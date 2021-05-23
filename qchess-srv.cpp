#include "header/board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_board(Board&);
void promote_piece(Piece&);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main (int argc, char* argv[]) {
   int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     // create a socket
     // socket(int domain, int type, int protocol)
     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     int enable=1;
     if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	error("setsockopt(SO_REUSEADDR) failed");

     // clear address structure
     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     /* setup the host_addr structure for use in bind call */
     // server byte order
     serv_addr.sin_family = AF_INET;  

     // automatically be filled with current host's IP address
     serv_addr.sin_addr.s_addr = INADDR_ANY;  

     // convert short integer value for port must be converted into network byte order
     serv_addr.sin_port = htons(portno);

     // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
     // bind() passes file descriptor, the address structure, 
     // and the length of the address structure
     // This bind() call will bind  the socket to the current IP address on port, portno
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");

     // This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a backlog queue
     // until accept() call accepts the connection.
     // Here, we set the maximum size for the backlog queue to 5.
     listen(sockfd,5);

     // The accept() call actually accepts an incoming connection
     clilen = sizeof(cli_addr);

     // This accept() function will write the connecting client's address info 
     // into the the address structure and the size of that structure is clilen.
     // The accept() returns a new socket file descriptor for the accepted connection.
     // So, the original socket file descriptor can continue to be used 
     // for accepting new connections while the new socker file descriptor is used for
     // communicating with the connected client.
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));


     // This send() function sends the 13 bytes of the string to the new socket
     send(newsockfd, "Hello, world!\n", 13, 0);

     bzero(buffer,256);

     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);

     close(newsockfd);
     close(sockfd);
     return 0; 
    Board b;
    std::string input;
    print_board(b);

    std::cout << "\nTurn for " << b.get_turn() <<": ";
    while (getline(std::cin, input)) {
        if (input == "quit") break;
        if (input == "p") {
            print_board(b);
        } else if (input[0] >= 'a' && input[0] <= 'h') {
            Position pos;
            try {
              pos = {input.at(0), input.at(1)};
            } catch (const std::out_of_range& oor) {
              std::cout << "You made a boo-boo, try again: ";
              continue;
            }
            while (true) {
                //select a piece
                std::vector<Position> moves;
                try {
                    Piece& p = b.select(pos);
                    echelon ech = p.get_random_ech();
                    //if selected piece is a pawn and on the last rank, promote it
                    if (ech == echelon::pawn && b.get_turn() == "black" && p.get_pos().rank == '1') {
                        promote_piece(p);
                        b.give_turn();
                        goto end_of_main_loop;
                    } else if (ech == echelon::pawn && b.get_turn() == "white" && p.get_pos().rank == '8') {
                        promote_piece(p);
                        b.give_turn();
                        goto end_of_main_loop;
                    }
                    std::cout << "The piece is a " << p.ech_to_long_str(ech) << "\n";
                    moves = b.get_moves(ech,p);
                    if (moves.empty()) {
                        std::cout << "I'm sorry, the piece has no legal moves!\nYou lose your turn!";
                        b.give_turn();
                        break;
                    }
                    std::cout << "Allowed moves: ";
                    for (Position pose: moves) {
                        std::cout << pose.file << pose.rank << " ";
                    }
                } catch(int e) {
                    std::cout << "I'm sorry, what?\n";
                    break;
                }
                //when a proper piece is selected, move it
                std::cout << "\nWhere do you want to move it to: ";
                getline(std::cin, input);
                while (true) {
                    try {
                        if (!(b.move(pos, Position {input.at(0), input.at(1)}, moves))) {
                            std::cout << "(mov)I'm sorry Dave, I can't allow you to do that. Where to: ";
                            getline(std::cin, input);
                            continue;
                        }
                    } catch (const std::out_of_range& oor) {
                        std::cout << "(oor)I'm sorry Dave, I can't allow you to do that. Where to: ";
                        getline(std::cin, input);
                        continue;
                    } catch (int e) {
                        std::cout << "(int)I'm sorry Dave, I can't allow you to do that. Where to: ";
                        getline(std::cin, input);
                        continue;
                    }
                    break;
                }
                //check for pawn promotion
                try {
                    Piece& p = b.need_promote();
                    promote_piece(p);
                } catch (int e)  {
                }
                print_board(b);
                break;
            }
       } else
        std::cout << "?";
end_of_main_loop:
        std::cout << "\nTurn for " << b.get_turn() <<": ";
    }
}

void promote_piece(Piece& p) {
    std::string input;
    std::cout << "Wow! You can upgrade that piece! What do you wanna upgrade to? q/b/n/r: ";
    getline(std::cin, input);
    while (true) {
        try {
            p.promote(input.at(2));
        } catch (const std::out_of_range& oor) {
            std::cout << "(oor)I'm sorry Dave, I can't allow you to do that. Update to: ";
            getline(std::cin, input);
            continue;
        } catch (int e) {
            std::cout << "(int)I'm sorry Dave, I can't allow you to do that. Update to: ";
            getline(std::cin, input);
            continue;
        }
        break;
    }
    std::cout << input << " it is then!\n";
}

void print_board(Board& b) {
/*    Player& wp = b.get_player("white");
    Player& bp = b.get_player("black");
        std::cout << "white pieces:\n";
    for (const Piece& p: wp.get_pieces()) {
        std::cout << p.get_pos().file << p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.alive?"ALIVE":"DEAD") << (p.quantum_known?" QKNOW":" QUNK") << (p.has_moved?" MOVED":" NOTMV") << "\n";
    }
    std::cout << "\nblack pieces:\n";
    for (const Piece& p: bp.get_pieces()) {
        std::cout << p.get_pos().file << p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.alive?"ALIVE":"DEAD") << (p.quantum_known?" QKNOW":" QUNK") << (p.has_moved?" MOVED":" NOTMV") << "\n";
    }
    std::cout << "\n";//*/
    std::cout << "    .------.------.------.------.------.------.------.------.\n";
    std::cout << "    |      |      |      |      |      |      |      |      |\n";
    for (char c = '8'; c >= '1'; --c) {
        std::cout << " " << c << "  |  ";
        for (char d = 'a'; d <= 'h'; ++d) {
            Position pos {d,c};
            std::cout << b.get_piece_str(pos);
            std::cout << "  |";
            if (d < 'h') std::cout << "  ";
        }
        std::cout << "\n    |      |      |      |      |      |      |      |      |\n";
        if (c == '1') {
            std::cout <<   "    .------.------.------.------.------.------.------.------.\n";
            break;
        }
        std::cout << "    .------+------+------+------+------+------+------+------.\n";
        std::cout << "    |      |      |      |      |      |      |      |      |\n";
    }
    std::cout << "\n       a      b      c      d      e      f      g      h\n";
}
