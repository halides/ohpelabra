#include "piece.h"

/*class Piece {
    char rank; //1-8
    char file; //a-h
    color col;
  public:
    void set_pos(char, char);
    Piece (char, char, color);
};*/

Piece::Piece (char r, char f, color c) {
    rank = r;
    file = f;
    col = c;
};
