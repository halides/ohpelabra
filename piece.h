enum class echelon {pawn, knight, bishop, rook, queen, king};

struct Position {
    char file; //a-h
    char rank; //1-8

    bool operator==(const Position rhs) {
         if (rank == rhs.rank && file == rhs.file) return true;
         return false;
    }

    Position& operator=(const Position rhs) {
         file = rhs.file; rank = rhs.rank;
         return *this;
    } //this is unnecessary, sort of!
};

class Piece {
    Position pos;
    echelon ech;
    echelon qech; //quantum echelon
    bool state; //dead or alive
    bool quantum_known; //is the quantum echelon known?
    
  public:
    bool has_moved; //has it moved? important for pawns (and for castling)

    const char* ech_to_str(echelon) const;

    Piece(Position, echelon, echelon);
    void set_pos(Position);
    echelon get_random_ech() const;
    void set_state(bool);
    bool get_state() const;
    Position get_pos() const;
    const char* get_ech() const;
    const char* get_qech() const;
};
