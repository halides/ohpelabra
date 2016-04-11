enum class color {white, black};

class Piece {
    char rank; //1-8
    char file; //a-h
    color col;
  public:
    void set_pos(char, char);
    Piece (char, char, color);
};
