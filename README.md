# ohpelabra

## Trying to build a quantum chess with C++

http://research.cs.queensu.ca/Parallel/QuantumChess/QuantumChess.html

gcc 4.9.2, using C++14. (g++-4.9 -g -Wall -std=c++14)

make && ./qchess
make clean

Some sort of MVC with a CLI (the CLI might not even be in C++).

Board has two Players, each Player has 16 Pieces, each Piece knows how to move?

- board.getState() gives state of board as a string or whatnot.
- board.move(player, pos1, pos2)
