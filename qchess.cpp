#include "board.h"
#include <iostream>

int main () {
    std::cout << "hello quantum world\n\n";
    Board b;
    Player& wp = b.get_player("white");
    for (const Piece& p: wp.get_pieces()) {
        std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << "\n";
    }
    std::cout << "\n";

    Position from {2, 'b'};
    Position to {4, 'b'};
//    from.rank=2; from.file='b';
//    to.rank=4; to.file='b';
    wp.move(from, to);
    wp.move(Position {2, 'c'}, Position {3, 'c'});

    for (const Piece& p: wp.get_pieces()) {
        std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << "\n";
    }
 /*    Player& bp = b.get_player("black");
    for (const Piece& p: bp.get_pieces()) {
        std::cout << p.get_pos().file << (int)p.get_pos().rank << ": " << p.get_ech() << " q: " << p.get_qech() << "\n";
    }*/

}
