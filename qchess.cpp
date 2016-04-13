#include "board.h"
#include <iostream>

using namespace std;

int main () {
    cout << "hello quantum world\n";
    Board b;
    Player wp = b.get_player("white");
    Player bp = b.get_player("black");
}
