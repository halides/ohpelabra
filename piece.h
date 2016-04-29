#pragma once
#include <string>

enum class color {white, black};
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
    } //this is unnecessary, the compiler does this
};

class Piece {
  private:
    Position pos;
    echelon ech;
    echelon qech; //quantum echelon
    std::string last_state;
    
  public:
    bool quantum_known; //is the quantum echelon known?
    bool alive; //dead or alive
    bool has_moved; //has it moved? important for pawns (and for castling)
    bool promote_ech;
    bool promote_qech;

    std::string ech_to_str(echelon) const;
    std::string ech_to_long_str(echelon) const;

    Piece(Position, echelon, echelon);
    Piece() {};
    void promote(char);
    void reset_promote();
    void set_pos(Position, color);
    echelon get_random_ech();
    Position get_pos() const;
    std::string get_ech() const;
    std::string get_qech() const;
};
