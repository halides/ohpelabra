#include "board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

int main () {
    std::cout << "hello quantum world\n\n";
    Board b;
    Player& wp = b.get_player("white");
    Player& bp = b.get_player("black");
    std::string input;

    std::cout << "\n\nCommands: (s)elect, quit, (p)rint\n\nPlease input command: ";
    while (getline(std::cin, input)) {
        std::cout << "input: " << input << std::endl;

        if (input == "quit") break;

        if (input == "print" || input == "p") {
            std::cout << "white pieces:\n";
            for (const Piece& p: wp.get_pieces()) {
                std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.get_state()?"ALIVE":"DEAD") << "\n";
            }
            std::cout << "\nblack pieces:\n";
            for (const Piece& p: bp.get_pieces()) {
                std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << " " << (p.get_state()?"ALIVE":"DEAD") << "\n";
            }
            std::cout << "\n";
        }

        if (input.compare(0,2,"s ") == 0) {
            Position pos {input.at(2), input.at(3)-48}; //yay magic!
            for (Piece& p: wp.get_pieces()) {
                if(p.get_pos() == pos) {
                     echelon ech = p.get_random_ech();
                     for (Position pose: b.get_moves(ech, p)) {
                         std::cout << "a pose: "<< pose.file << (int)pose.rank << std::endl;
                     }
                     std::cout << "The piece will be: " << p.ech_to_str(ech) << "\nWhere do you want to move it to: ";
                     break;
                }
            }
            getline(std::cin, input);
            wp.move(pos, Position {input.at(0), input.at(1)-48});
        }

        std::cout << "Please input command: ";
    }
}
