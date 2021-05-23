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

std::string print_board(Board&);
void promote_piece(Piece&);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main (int argc, char* argv[]) {
    int sockfd, sockfd1, sockfd2, portno;
    socklen_t clilen;
    char buffer[3356];
    bzero(buffer,3356);
    struct sockaddr_in serv_addr, cli_addr;
    int n;
 
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

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
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
printf("BIND ok, waiting for clients...\n");
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
    sockfd1 = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (sockfd1 < 0) 
          error("ERROR on accept");

    printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
//    send(sockfd1, "Hello, you play white!\nWaiting for opponent...", 3356, 0);

    sockfd2 = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (sockfd2 < 0) 
          error("ERROR on accept");

    printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
  //  send(sockfd2, "Hello, you play black!", 3356, 0);

    Board b;
    std::string input;
    std::string to_send;













    while(1) {
	    to_send += print_board(b);
        bzero(buffer,3356);
	if (b.get_turn() == "white") {
		send(sockfd1, to_send.c_str(), to_send.length(), 0);
	    recv(sockfd1,buffer,255,0);
	} else {
		send(sockfd2, to_send.c_str(), to_send.length(), 0);
	    recv(sockfd2,buffer,255,0);
	}
	input = buffer;
	if (!input.empty() && input[input.length()-1] == '\n') {
          input.erase(input.length()-1);
        }
	std::cout << " -- Input: >" << input << "<\n";

	    to_send = "";

	if (input[0] >= 'a' && input[0] <= 'h') {
            Position pos;
            try {
              pos = {input.at(0), input.at(1)};
            } catch (const std::out_of_range& oor) {
		    to_send="Try Again!";
              continue;
            }
	    std::cout << "pos: " << input.at(0) << input.at(1) << "\n";
            while (true) {
		    to_send="";

         //select a piece
                std::vector<Position> moves;
                try {
                    Piece& p = b.select(pos);
                    echelon ech = p.get_random_ech();
                    //if selected piece is a pawn and on the last rank, promote it
/*                    if (ech == echelon::pawn && b.get_turn() == "black" && p.get_pos().rank == '1') {
                        promote_piece(p);
                        b.give_turn();
                        goto end_of_main_loop;
                    } else if (ech == echelon::pawn && b.get_turn() == "white" && p.get_pos().rank == '8') {
                        promote_piece(p);
                        b.give_turn();
                        goto end_of_main_loop;
                    }*/
                    to_send = "The piece is a "; to_send += p.ech_to_long_str(ech); to_send += "\n";
                    moves = b.get_moves(ech,p);
                    if (moves.empty()) {
                        to_send += "I'm sorry, the piece has no legal moves!\nYou lose your turn!";
	                b.give_turn();
                        break;
                    }
                    to_send += "Allowed moves: ";
                    for (Position pose: moves) {
                        to_send += pose.file; to_send += pose.rank; to_send += " ";
                    }
                } catch(int e) {
			to_send += "Try Again!\n";
                    break;
                }
	//	std::cout << "paskaa\n\n---\n" << to_send.c_str() << "---\n\n";
		if (b.get_turn() == "white")
                send(sockfd1, to_send.c_str(), to_send.length(), 0);
              else
                send(sockfd2, to_send.c_str(), to_send.length(), 0);

                //when a proper piece is selected, move it
                while (true) {
        bzero(buffer,3356);
       	if (b.get_turn() == "white") {
		    send(sockfd1, "Where to: ", 10, 0);
	    recv(sockfd1,buffer,255,0);
	} else {
		    send(sockfd2, "Where to:", 10, 0);
	    recv(sockfd2,buffer,255,0);
	}
	input = buffer;
	if (!input.empty() && input[input.length()-1] == '\n') {
          input.erase(input.length()-1);
        }
	std::cout << " -- Input: >" << input << "<\n";

                    try {
                        if (!(b.move(pos, Position {input.at(0), input.at(1)}, moves))) {
                            continue;
                        } else {
			to_send="";
			}
                    } catch (const std::out_of_range& oor) {
                        continue;
                    } catch (int e) {
                        continue;
                    }
                    break;
                }
                break;
            }
       }
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

std::string print_board(Board& b) {
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
    std::string s;
    s = "    .----.----.----.----.----.----.----.----.\n";
//    s += "    |    |    |    |    |    |    |    |    |\n";
    for (char c = '8'; c >= '1'; --c) {
        s += " "; s+= c; s+= "  | ";
        for (char d = 'a'; d <= 'h'; ++d) {
            Position pos {d,c};
            s += b.get_piece_str(pos);
            s += " |";
            if (d < 'h') s += " ";
        }
	  s += "\n";
//        s += "\n    |    |    |    |    |     |    |    |    |\n";
        if (c == '1') {
            s +=   "    .----.----.----.----.----.----.----.----.\n";
            break;
        }
        s += "    .----+----+----+----+----+----+----+----.\n";
//        s += "    |    |    |    |    |    |    |    |    |\n";
    }
    s += "\n       a    b    c    d    e    f    g    h\n";
    return s;
}
