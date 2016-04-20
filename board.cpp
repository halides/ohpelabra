#include "board.h"

Board::Board() { // : wp(color::white), bp(color::black) {
    wp = Player(color::white); //either or, player.h
    bp = Player(color::black); //this one is slower
    t = turn::white;
}

Player& Board::get_player(std::string s) {
    if (s == "white") {
	return wp;
    } else {
        return bp;
    }
}

sqr_state Board::is_free(Position pos) {
    for (Piece& p: wp.get_pieces()) {
        if (pos == p.get_pos()) {
             return sqr_state::white;
        }
    }
    for (Piece& p: bp.get_pieces()) {
        if (pos == p.get_pos()) {
             return sqr_state::black;
        }
    }
    return sqr_state::free;
}

std::vector<Position> Board::get_moves(echelon e, Piece& p) {
    std::vector<Position> poses;
    Position pos = p.get_pos();
    Position tmpos;
    if (t == turn::white) {
        switch(e) {
          case echelon::pawn:
            tmpos = {pos.file, pos.rank+1};
            if (is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                if(!p.has_moved) {
                    p.has_moved=true;
                    tmpos = {pos.file, pos.rank+2};
                    if (is_free(tmpos) == sqr_state::free)
                    poses.push_back(tmpos);
                }
            }
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
