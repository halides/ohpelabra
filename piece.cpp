#include "piece.h"

Piece::Piece(char r, char f, echelon e) {
    set_pos(r,f);
}

int Piece::set_pos(char r, char f) {
    if (r < 'a' || r > 'h' || f < 1 || f > 8) {
        return 1;
    } else {
        rank = r;
        file = f;
        return 0;
    }
}
