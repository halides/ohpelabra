#include "piece.h"

class Out_of_board {};

class Position {
    char rank; //1-8
    char file; //a-h
  public:
    Position (char, char);
};

Position::Position (char rank, char file) {
    if (rank < 1 || rank > 8 || file < 'a' || file > 'h') throw Out_of_board();
    this->rank = rank;
    this->file = file;
};

class Piece {
    enum class color {white, black};
  public:
    void set_pos(char, char);
    Piece (Position);
};

Piece::Piece (Position pos) {

};
