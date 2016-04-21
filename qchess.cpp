#include "board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

void print_board(Board&);

int main () {
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
              std::cout << "You made a boo-boo, try again\n";
              continue;
            }
            while (true) {
                std::vector<Position> moves;
                try {
                    Piece& p = b.select(pos);
                    echelon ech = p.get_random_ech();
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
                print_board(b);
                break;
            }
       } else
        std::cout << "?";

        std::cout << "\nTurn for " << b.get_turn() <<": ";
    }
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
    std::cout << "\n";
    std::cout << "a printout\n";//*/
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
}
