enum class echelon {pawn, knight, bishop, rook, queen, king};

class Piece {
    char rank; //1-8
    char file; //a-h
    echelon ech;
    
  public:
    Piece(char, char, echelon);
    int set_pos(char, char);
    char get_pos();
};
