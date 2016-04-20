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
   if (pos.file < 'a' || pos.file > 'h' || pos.rank < 1 || pos.rank > 8) return sqr_state::illegal;
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
            tmpos = {pos.file-1, pos.rank+1};
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file+1, pos.rank+1};
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            
            break;

          case echelon::knight:
            if(!p.has_moved)
                p.has_moved=true;
            tmpos = {pos.file+2, pos.rank+1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file+2, pos.rank-1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file-2, pos.rank+1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file-2, pos.rank-1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file+1, pos.rank-2};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file-1, pos.rank-2};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file+1, pos.rank+2};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {pos.file-1, pos.rank+2};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            break;

          case echelon::bishop:
            tmpos = {pos.file+1, pos.rank+1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file+1, pos.rank-1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank+1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank-1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;
          case echelon::rook:
            tmpos = {pos.file+1, pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, pos.rank+1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, pos.rank-1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;
          case echelon::queen:
            tmpos = {pos.file+1, pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, pos.rank+1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, pos.rank-1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file+1, pos.rank+1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file+1, pos.rank-1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank+1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank-1};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;
          case echelon::king:
            tmpos = {pos.file-1, pos.rank-1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file-1, pos.rank+1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, pos.rank+1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file+1, pos.rank+1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file+1, pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file+1, pos.rank-1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, pos.rank-1};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;
          default:;
        }
    } else {

    }
    return poses;
}
