#include "board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

int main () {
    Board b;
    Player& wp = b.get_player("white");
    Player& bp = b.get_player("black");
    std::string input;

    std::cout << "\n\nCommands: (s)elect, quit, (p)rint\n\nTurn for " << b.get_turn() <<": ";
    while (getline(std::cin, input)) {
        std::cout << "input: " << input << std::endl;


        if (input == "quit") break;

        if (input == "print" || input == "p") {
            std::cout << "white pieces:\n";
            for (const Piece& p: wp.get_pieces()) {
                std::cout << p.get_pos().file << p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.alive?"ALIVE":"DEAD") << "\n";
            }
            std::cout << "\nblack pieces:\n";
            for (const Piece& p: bp.get_pieces()) {
                std::cout << p.get_pos().file << p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.alive?"ALIVE":"DEAD") << "\n";
            }
            std::cout << "\n";
            std::cout << "a printout\n";
        } else if (input.compare(0,2,"s ") == 0) {
            Position pos {input.at(2), input.at(3)};
            while (true) {
                Piece p;
                try {
                    p = b.select(pos);
                } catch(int e) {
                    std::cout << "I'm sorry, what?\n";
                    break;
                }
                echelon ech = p.get_random_ech();
                std::vector<Position> moves = b.get_moves(ech,p);
                if (moves.empty()) {
                    std::cout << "I'm sorry, the piece has no legal moves!\n";
                    b.give_turn();
                    break;
                }
                for (Position pose: moves) {
                    std::cout << pose.file << pose.rank << " ";
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
