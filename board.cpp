#include "board.h"

Board::Board() : wp(color::white), bp(color::black) {
    srand(time(0)); //1Hz
//    wp = Player(color::white); //either or, player.h
//    bp = Player(color::black); //this one is slower
}

Player Board::get_player(std::string s) {
    if (s == "white") {
        return wp;
    } else {
        return bp;
    }
}

