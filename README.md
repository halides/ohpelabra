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

Hours:
- 5.4 1h create repo
- 8.4 1h think about stuff, mod readme
- 11.4 4h basic structure, lots of reading up on C++
