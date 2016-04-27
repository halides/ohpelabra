#include "board.h"
#include <string>
#include <algorithm>
#include <iostream>

Board::Board() { // : wp(color::white), bp(color::black) {
    wp = Player(color::white); //either or, player.h
    bp = Player(color::black); //this one is slower
    t = turn::white;
}

Player& Board::get_player(std::string s) {
    if (s == "white") {
	return wp;
    } else if (s == "black") {
        return bp;
    }
}

Piece& Board::need_update() {
    for(Piece& p: wp.get_pieces()) {
        if (p.update_ech || p.update_qech) {
            p.reset_update();
            return p;
        }
    }
    for(Piece& p: bp.get_pieces()) {
        if (p.update_ech || p.update_qech) {
            p.reset_update();
            return p;
        }
    }
    throw 1;
}

std::string Board::get_piece_str(Position pos) {
    std::string s;
    for(Piece& p: wp.get_pieces()) {
        if (p.get_pos() == pos && p.alive) {
            s = p.get_ech();
            if (p.quantum_known) s += p.get_qech();
            else s += "?";
            return s;
        }
    }
    for(Piece& p: bp.get_pieces()) {
        if (p.get_pos() == pos && p.alive) {
            s = p.get_ech();
            if (p.quantum_known) s += p.get_qech();
            else s += "?";
            std::transform(s.begin(), s.end(),s.begin(), ::toupper);
            return s;
        }
    }
    return "  ";
}

void Board::give_turn() {
    if (t == turn::white) t = turn::black;
    else if (t == turn::black) t = turn::white;
}

bool Board::move(Position from, Position to, std::vector<Position> moves) {
    bool ok = false; //is the move correct
    int i_erase = 0; //counter 
    for (Position pos: moves) {
        if (to == pos) {
            ok = true;
            break;
        }
    }
    if (!ok) return false;
    if (t == turn::white) {
        if (wp.move(from, to)) {
            for (Piece& p: bp.get_pieces()) {
                if (to == p.get_pos()) {
                    if (p.get_ech() == "k") {
                        std::cout << "\n\n\nOMG White player won!\n\n\n";
                        exit(0);
                    }
                    bp.get_pieces().erase(bp.get_pieces().begin()+i_erase);
                    break;
                }
                i_erase++;
            }
        t = turn::black;
        return true;
        }
    } else if (t == turn::black) {
        if (bp.move(from, to)) {
            for (Piece& p: wp.get_pieces()) {
                if (to == p.get_pos()) {
                    if (p.get_ech() == "k") {
                        std::cout << "\n\n\nOMG Black player won!\n\n\n";
                        exit(0);
                    }
                    wp.get_pieces().erase(wp.get_pieces().begin()+i_erase);
                    break;
                }
                i_erase++;
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
    else if (t == turn::black) return "black";
}

sqr_state Board::is_free(Position pos) {
   if (pos.file < 'a' || pos.file > 'h' || pos.rank < '1' || pos.rank > '8') return sqr_state::illegal;
   for (Piece& p: wp.get_pieces()) {
        if (pos == p.get_pos() && p.alive) {
             return sqr_state::white;
        }
    }
    for (Piece& p: bp.get_pieces()) {
        if (pos == p.get_pos() && p.alive) {
             return sqr_state::black;
        }
    }
    return sqr_state::free;
}

std::vector<Position> Board::get_moves(echelon e, Piece& p) {
    std::vector<Position> poses;
    Position pos = p.get_pos();
    Position tmpos;
    sqr_state sqr_st_opp;
    int pawn_dir = 1;
    if (t == turn::white) {
        sqr_st_opp = sqr_state::black;
    } else if (t == turn::black) {
        sqr_st_opp = sqr_state::white;
        pawn_dir = -1;
    }
        switch(e) {
          case echelon::pawn:
            tmpos = {pos.file, static_cast<char>(pos.rank+pawn_dir)};
            if (is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                if(!p.has_moved) {
                    tmpos = {pos.file, static_cast<char>(pos.rank+pawn_dir+pawn_dir)};
                    if (is_free(tmpos) == sqr_state::free)
                    poses.push_back(tmpos);
                }
            }
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+pawn_dir)};
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+pawn_dir)};
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            
            break;

          case echelon::knight:
            tmpos = {static_cast<char>(pos.file+2), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+2), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-2), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-2), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+2)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);
            break;

          case echelon::bishop:
            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            break;

          case echelon::rook:
            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            break;

          case echelon::queen:
            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file++; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank++;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            while(is_free(tmpos) == sqr_state::free) {
                poses.push_back(tmpos);
                tmpos.file--; tmpos.rank--;
            }
            if (is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            break;

          case echelon::king:
            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file-1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank+1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), pos.rank};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {static_cast<char>(pos.file+1), static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            tmpos = {pos.file, static_cast<char>(pos.rank-1)};
            if (is_free(tmpos) == sqr_state::free || is_free(tmpos) == sqr_st_opp)
                poses.push_back(tmpos);

            break;
          default:;
        }
    return poses;
}
