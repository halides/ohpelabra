#include "player.h"
#include <iostream>
#include <algorithm>

Player::Player(color c) {
    pcolor = c;

    Position pos;
    std::vector<echelon> qp;

    for (int i=0; i<8; i++) {
        qp.push_back(echelon::pawn);
    }
    qp.push_back(echelon::knight);
    qp.push_back(echelon::knight);
    qp.push_back(echelon::bishop);
    qp.push_back(echelon::bishop);
    qp.push_back(echelon::rook);
    qp.push_back(echelon::rook);
    qp.push_back(echelon::queen);

    srand(time(0));
    if (pcolor == color::white) {
        std::random_shuffle(qp.begin(), qp.end());
    }
    std::random_shuffle(qp.begin(), qp.end());

    for (int i=1; i<9; i++) {
        pos.rank = (pcolor == color::white)?'2':'7'; //i just love the trinary operator
        pos.file = 96+i; //ASCII 'a' == 97
        pieces.push_back(Piece(pos, echelon::pawn, qp.back()));
        qp.pop_back();
    }
    pos.rank = (pcolor == color::white)?'1':'8';

    pos.file='a';
    put_qp(pieces, pos, echelon::rook, qp);
    pos.file='h';
    put_qp(pieces, pos, echelon::rook, qp);


    pos.file='b';
    put_qp(pieces, pos, echelon::knight, qp);
    pos.file='g';
    put_qp(pieces, pos, echelon::knight, qp);

    pos.file='c';
    put_qp(pieces, pos, echelon::bishop, qp);
    pos.file='f';
    put_qp(pieces, pos, echelon::bishop, qp);

    pos.file='d';
    put_qp(pieces, pos, echelon::queen, qp);
    pos.file='e';
    put_qp(pieces, pos, echelon::king, qp);

}

void Player::put_qp(std::vector<Piece>& pieces, Position& pos, echelon ech, std::vector<echelon>& qp) {
    pieces.push_back(Piece(pos, ech, qp.back()));
    qp.pop_back();
}

bool Player::move(Position from, Position to) {
    for (Piece& p: pieces) {
        if (p.get_pos() == from) {
            p.set_pos(to, pcolor);
            return true;
        }
    }
    return false;
}

std::vector<Piece>& Player::get_pieces() {
    return pieces;
}
