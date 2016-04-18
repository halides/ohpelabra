#include "board.h"
#include <iostream>
#include <sstream>
#include <string>

int main () {
    std::cout << "hello quantum world\n\n";
    Board b;
    Player& wp = b.get_player("white");
    Player& bp = b.get_player("black");
    std::string input;

    std::cout << "\n\nCommands: (m)ove, quit, (p)rint\n\nPlease input command: ";
    while (getline(std::cin, input)) {
        std::cout << "input: " << input << std::endl;

        if (input == "quit") break;

        if (input == "print" || input == "p") {
            std::cout << "white pieces:\n";
            for (const Piece& p: wp.get_pieces()) {
                std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << "\n";
            }
            std::cout << "\nblack pieces:\n";
            for (const Piece& p: bp.get_pieces()) {
                std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << "\n";
            }
            std::cout << "\n";
        }

        if (input.compare(0,2,"m ") == 0 || input.compare(0,5,"move ") == 0) {
            int pad = 2;
            if (input.compare(0,5,"move ") == 0) {
                pad = 5;
            }
            std::cout << input << " you want to move eh?\n";
            wp.move(Position {input.at(pad), input.at(pad+1)-48}, Position {input.at(pad+3), input.at(pad+4)-48});
            std::cout << input.at(pad) << input.at(pad+1) << input.at(pad+3) << input.at(pad+4);
        }

        std::cout << "Please input command: ";
    }


/*        Position from {2, 'b'};
        Position to {4, 'b'};
    //    from.rank=2; from.file='b';
    //    to.rank=4; to.file='b';
        wp.move(from, to);
  Player& bp = b.get_player("black");
    for (const Piece& p: bp.get_pieces()) {
        std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << "\n";
    }*/

}
