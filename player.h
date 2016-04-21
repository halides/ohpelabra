#pragma once
#include <vector>
#include "piece.h"

enum class color {white, black};

class Player {
    color col;
  public:
    std::vector<Piece> pieces;
    Player(){} //either or, board.cpp
    Player(color);
    bool move(Position, Position);
    std::vector<Piece>& get_pieces();
};
