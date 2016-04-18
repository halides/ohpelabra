#include <vector>
#include "piece.h"

enum class color {white, black};

class Player {
    std::vector<Piece> pieces;
    color col;
  public:
    Player(){} //either or, board.cpp
    Player(color);
    void move(Position, Position);
    const std::vector<Piece>& get_pieces();
};
