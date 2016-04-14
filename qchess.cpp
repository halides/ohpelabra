#include "board.h"
#include <iostream>

int main () {
    std::cout << "hello quantum world\n";
    Board b;
    Player& wp = b.get_player("white");
    Player& bp = b.get_player("black");
}
