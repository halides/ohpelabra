#pragma once
#include <vector>
#include "piece.h"

enum class color {white, black};

class Player {
    std::vector<Piece> pieces;
    color col;
  public:
    Player(){} //either or, board.cpp
    Player(color);
    bool move(Position, Position);
    std::vector<Piece>& get_pieces();
};
