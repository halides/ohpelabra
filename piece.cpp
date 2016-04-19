#include "piece.h"
#include <iostream>
#include <algorithm>

Piece::Piece(Position p, echelon e, echelon qe) {
    try {
        set_pos(p);
    } catch (int e) {
std::cout << "abua";
        throw;
    }
    state = true; //alive
    has_moved = false; //has not moved yet
    ech = e;
    qech = qe;
}

void Piece::set_pos(Position p) {
    if (p.file < 'a' || p.file > 'h' || p.rank < 1 || p.rank > 8) {
        throw 2;
    } else {
        pos.rank = p.rank;
        pos.file = p.file;
    }
}

echelon Piece::get_random_ech() const {
    if(rand()%2) {
        return ech;
    } else {
        return qech;
    }
}

void Piece::set_state(bool s) {
    state = s;
}

bool Piece::get_state() const {
    return state;
}

Position Piece::get_pos() const {
    return pos;
}

const char* Piece::get_ech() const {
    return ech_to_str(ech);
}

const char* Piece::get_qech() const {
    return ech_to_str(qech);
}

const char* Piece::ech_to_str(echelon e) const {
    switch(e) {
      case echelon::pawn: return "pawn";
      case echelon::knight: return "knight";
      case echelon::bishop: return "bishop";
      case echelon::rook: return "rook";
      case echelon::queen: return "queen";
      case echelon::king: return "king";
      default: return "error";
    }
}
