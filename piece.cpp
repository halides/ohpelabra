#include "piece.h"

Piece::Piece(Position p, echelon e, echelon qe) {
    try {
        set_pos(p);
    } catch (int e) {
        throw;
    }
    state = true; //alive
    ech = e;
    qech = qe;
}

void Piece::set_pos(Position p) {
    if (p.file < 'a' || p.file > 'h' || p.rank < 1 || p.rank > 8) {
        throw 1;
    } else {
        rank = p.rank;
        file = p.file;
    }
}

void Piece::set_state(bool s) {
    state = s;
}
