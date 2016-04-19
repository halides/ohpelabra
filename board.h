#include "player.h"
#include <string>
enum class turn {white, black};

class Board {
    Player wp;
    Player bp;
    turn t;
  public:
    Board();
    Player& get_player(std::string);
    const std::vector<Position> get_moves(echelon, Piece);
};
