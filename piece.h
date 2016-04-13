enum class echelon {pawn, knight, bishop, rook, queen, king};

struct Position {
    char rank; //1-8
    char file; //a-h
};

class Piece {
    Position pos;
    echelon ech;
    echelon qech; //quantum echelon
    bool state; //dead or alive
    const char* ech_to_str(echelon) const;
    
  public:
    Piece(Position, echelon, echelon);
    void set_pos(Position);
    void set_state(bool);
    Position get_pos() const;
    const char* get_ech() const;
    const char* get_qech() const;
};
