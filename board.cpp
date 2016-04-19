#include "board.h"

Board::Board() { // : wp(color::white), bp(color::black) {
    wp = Player(color::white); //either or, player.h
    bp = Player(color::black); //this one is slower
}

Player& Board::get_player(std::string s) {
    if (s == "white") {
        return wp;
    } else {
        return bp;
    }
}

std::vector<Position> Board::get_moves(echelon e, Piece p) {
    std::vector<Position> poses;
    Position pos = p.get_pos();
    if (t == turn::white) {
        switch(e) {
          case echelon::pawn:
            if(!p.has_moved) {
//                p.has_moved=true;
                poses.push_back(Position {pos.file, pos.rank+2});
            }
                poses.push_back(Position {pos.file, pos.rank+1});
            break;
          case echelon::knight:
            break;
          case echelon::bishop:
            break;
          case echelon::rook:
            break;
          case echelon::queen:
            break;
          case echelon::king:
            break;
          default:;
        }
    } else {

    }
    return poses;
}
