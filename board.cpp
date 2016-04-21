#include "board.h"
#include <string>

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

void Board::give_turn() {
    if (t == turn::white) t = turn::black;
    else t = turn::white;
}

bool Board::move(Position from, Position to, std::vector<Position> moves) {
    bool ok = false;
    for (Position pos: moves) {
        if (to == pos) ok = true;
    }
    if (!ok) return false;
    if (t == turn::white) {
        if (wp.move(from, to)) {
            for (Piece& p: bp.get_pieces()) {
                if (to == p.get_pos()) {
                    p.alive=false;
                    break;
                }
            }
        t = turn::black;
        return true;
        }
    }
    else {
        if (bp.move(from, to)) {
            for (Piece& p: wp.get_pieces()) {
                if (to == p.get_pos()) {
                    p.alive=false;
                    break;
                }
            }
        t = turn::white;
        return true;
        }
    }
    return false;
}

Piece& Board::select(Position pos) {
    if (t == turn::white) {
        for (Piece& p: wp.get_pieces()) {
            if(p.get_pos() == pos) {
                 return p;
            }
        }
    } else {
     for (Piece& p: bp.get_pieces()) {
            if(p.get_pos() == pos) {
                 return p;
            }
        }
    }
    throw 1;
}

std::string Board::get_turn() {
    if (t == turn::white) return "white";
    return "black";
}

sqr_state Board::is_free(Position pos) {
   if (pos.file < 'a' || pos.file > 'h' || pos.rank < '1' || pos.rank > '8') return sqr_state::illegal;
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
            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                if(!p.has_moved) {
                    tmpos = {pos.file, static_cast<char>(pos.rank+2)};
                    if (is_free(tmpos) == sqr_state::free)
                    poses.push_back(tmpos);
                }
            }
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            
            break;

          case echelon::knight:
            tmpos = {static_cast<char>(pos.file+2), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+2), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-2), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-2), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);
            break;

          case echelon::bishop:
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;

          case echelon::rook:
            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;

          case echelon::queen:
            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;

          case echelon::king:
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::black)
                poses.push_back(tmpos);

            break;
          default:;
        }
    } else {
        switch(e) {
          case echelon::pawn:
            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                if(!p.has_moved) {
                    tmpos = {pos.file, static_cast<char>(pos.rank-2)};
                    if (is_free(tmpos) == sqr_state::free)
                    poses.push_back(tmpos);
                }
            }
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            
            break;

          case echelon::knight:
            tmpos = {static_cast<char>(pos.file+2), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+2), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-2), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-2), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);
            break;

          case echelon::bishop:
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            break;

          case echelon::rook:
            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            break;

          case echelon::queen:
            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            break;

          case echelon::king:
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_state::white)
                poses.push_back(tmpos);

            break;
          default:;
        }

    }
    return poses;
}
