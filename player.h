#include <vector>
#include "piece.h"

enum class color {white, black};

class Player {
    std::vector<Piece> pieces;
    color col;
  public:
    Player(color);
};
