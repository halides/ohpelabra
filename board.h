#include "player.h"
#include <string>

class Board {
    Player wp;
    Player bp;
  public:
    Board();
    Player& get_player(std::string);
};
