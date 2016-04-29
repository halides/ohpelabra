#include <string>
#include "piece.h"
#include <iostream>
#include <algorithm>

Piece::Piece(Position p, echelon e, echelon qe) {
    try {
        set_pos(p, color::white);
    } catch (int e) {
        throw;
    }
    alive = true; //alive
    has_moved = false; //has not moved yet
    quantum_known = false; //we don't know the qech yet
    last_state = "classic "; //nice stringy implementation
    promote_ech = false;
    promote_qech = false;
    ech = e;
    qech = qe;
}

void Piece::promote(char s) {
    if (last_state == "classic ") {
        if (s == 'q') ech = echelon::queen;
        else if (s == 'b') ech = echelon::bishop;
        else if (s == 'n') ech = echelon::knight;
        else if (s == 'r') ech = echelon::rook;
        else throw 1;
    } else if (last_state == "quantum ") {
        if (s == 'q') qech = echelon::queen;
        else if (s == 'b') qech = echelon::bishop;
        else if (s == 'n') qech = echelon::knight;
        else if (s == 'r') qech = echelon::rook;
        else throw 1;
    }
}

void Piece::reset_promote() {
    promote_ech = false;
    promote_qech = false;
}

void Piece::set_pos(Position p, color col) {
    has_moved = true;
    if (p.file < 'a' || p.file > 'h' || p.rank < '1' || p.rank > '8') {
        throw 2;
    }
    pos.rank = p.rank;
    pos.file = p.file;

    if (last_state == "classic " && ech == echelon::pawn && col == color::white && pos.rank == '8') {
        promote_ech = true;
    } else if (last_state == "quantum " && qech == echelon::pawn && col == color::white && pos.rank == '8') {
        promote_qech = true;
    } else if (last_state == "classic " && ech == echelon::pawn && col == color::black && pos.rank == '1') {
        promote_ech = true;
    } else if (last_state == "quantum " && qech == echelon::pawn && col == color::black && pos.rank == '1') {
        promote_qech = true;
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
