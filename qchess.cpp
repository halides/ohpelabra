#include "board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

int main () {
    Board b;
//    Player& wp = b.get_player("white");
//    Player& bp = b.get_player("black");
    std::string input;

    std::cout << "\n\nCommands: (s)elect, quit, (p)rint\n\nTurn for " << b.get_turn() <<": ";
    while (getline(std::cin, input)) {
        std::cout << "input: " << input << std::endl;


        if (input == "quit") break;

        if (input == "print" || input == "p") {
/*            std::cout << "white pieces:\n";
            for (const Piece& p: wp.get_pieces()) {
                std::cout << p.get_pos().file << p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.alive?"ALIVE":"DEAD") << (p.quantum_known?" QKNOW":" QUNK") << (p.has_moved?" MOVED":" NOTMV") << "\n";
            }
            std::cout << "\nblack pieces:\n";
            for (const Piece& p: bp.get_pieces()) {
                std::cout << p.get_pos().file << p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.alive?"ALIVE":"DEAD") << (p.quantum_known?" QKNOW":" QUNK") << (p.has_moved?" MOVED":" NOTMV") << "\n";
            }
            std::cout << "\n";
            std::cout << "a printout\n";*/
            std::cout << "    .------.------.------.------.------.------.------.------.\n";
            std::cout << "    |      |      |      |      |      |      |      |      |\n";
            for (char c = '8'; c >= '1'; c--) {
                std::cout << " " << c << "  |  ";
                for (char d = 'a'; d <= 'h'; d++) {
                    Position pos {d,c};
                    std::cout << b.get_piece_str(pos);
                    std::cout << "  |";
                    if (d < 'h') std::cout << "  ";
                }
                std::cout << "\n    |      |      |      |      |      |      |      |      |\n";
                std::cout <<   "    .------.------.------.------.------.------.------.------.\n";
                if (c == '1') break;
                std::cout << "    |      |      |      |      |      |      |      |      |\n";
            }
            std::cout << "\n       a      b      c      d      e      f      g      h\n";
        } else if (input.compare(0,2,"s ") == 0) {
            Position pos {input.at(2), input.at(3)};
            while (true) {
                std::vector<Position> moves;
                try {
                    Piece& p = b.select(pos);
                    echelon ech = p.get_random_ech();
                    std::cout << "The piece is a " << p.ech_to_long_str(ech) << "\n";
                    moves = b.get_moves(ech,p);
                    if (moves.empty()) {
                        std::cout << "I'm sorry, the piece has no legal moves!\n";
                        b.give_turn();
                        break;
                    }
                    for (Position pose: moves) {
                        std::cout << pose.file << pose.rank << " ";
                    }
                } catch(int e) {
                    std::cout << "I'm sorry, what?\n";
                    break;
                }
               std::cout << "\nWhere do you want to move it to: ";
                getline(std::cin, input);
                while (!(b.move(pos, Position {input.at(0), input.at(1)}, moves))) {
                    std::cout << "I'm sorry Dave, I can't allow you to do that. Where to: ";
                    getline(std::cin, input);
                }
                break;
            }
       } else
        std::cout << "\n\nCommands: (s)elect, quit, (p)rint";

        std::cout << "\n\nTurn for " << b.get_turn() <<": ";
    }
}
