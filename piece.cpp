#include <string>
#include "piece.h"
#include <iostream>
#include <algorithm>

Piece::Piece(Position p, echelon e, echelon qe) {
    try {
        set_pos(p);
    } catch (int e) {
        throw;
    }
    alive = true; //alive
    has_moved = false; //has not moved yet
    quantum_known = false;
    last_state = "classic ";
    ech = e;
    qech = qe;
}

void Piece::set_pos(Position p) {
    has_moved = true;
    if (p.file < 'a' || p.file > 'h' || p.rank < '1' || p.rank > '8') {
        throw 2;
    } else {
        pos.rank = p.rank;
        pos.file = p.file;
    }
}

echelon Piece::get_random_ech() {
    if(rand()%2) {
        last_state = "classic ";
        return ech;
    } else {
        last_state = "quantum ";
        quantum_known = true;
        return qech;
    }
}

Position Piece::get_pos() const {
    return pos;
}

std::string Piece::get_ech() const {
    return ech_to_str(ech);
}

std::string Piece::get_qech() const {
    return ech_to_str(qech);
}

std::string Piece::ech_to_str(echelon e) const {
    switch(e) {
      case echelon::pawn: return "p";
      case echelon::knight: return "n";
      case echelon::bishop: return "b";
      case echelon::rook: return "r";
      case echelon::queen: return "q";
      case echelon::king: return "k";
      default: return "error";
    }
}

std::string Piece::ech_to_long_str(echelon e) const {
    switch(e) {
      case echelon::pawn: return last_state+"pawn";
      case echelon::knight: return last_state+"knight";
      case echelon::bishop: return last_state+"bishop";
      case echelon::rook: return last_state+"rook";
      case echelon::queen: return last_state+"queen";
      case echelon::king: return last_state+"king";
      default: return "error";
    }
}
