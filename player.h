#pragma once
#include <vector>
#include "piece.h"

class Player {
  private:
    color pcolor;
    void put_qp(std::vector<Piece>&, Position&, echelon, std::vector<echelon>&);
  public:
    std::vector<Piece> pieces;
//    Player(){} //either or, board.cpp
    Player(color);
    bool move(Position, Position);
    std::vector<Piece>& get_pieces();
};
