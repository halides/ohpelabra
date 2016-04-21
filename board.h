#pragma once
#include "player.h"
#include <string>
enum class turn {white, black};
enum class sqr_state {free, white, black, illegal};

class Board {
    Player wp;
    Player bp;
    turn t;
  public:
    Board();
    Player& get_player(std::string);
    std::vector<Position> get_moves(echelon, Piece&);
    Piece& select(Position);
    bool move(Position, Position, std::vector<Position>);
    std::string get_turn();
    sqr_state is_free(Position);
    void give_turn();
};
