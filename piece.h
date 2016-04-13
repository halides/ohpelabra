enum class echelon {pawn, knight, bishop, rook, queen, king};

struct Position {
    char rank;
    char file;
};

class Piece {
    char rank; //1-8
    char file; //a-h
    echelon ech;
    echelon qech; //quantum echelon
    bool state; //dead or alive
    
  public:
    Piece(Position, echelon, echelon);
    void set_pos(Position);
    void set_state(bool);
    Position get_pos();
};
