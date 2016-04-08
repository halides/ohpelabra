# ohpelabra

## Trying to build a chess with C++

gcc-4.9.2

Some sort of MVC with a CLI (the CLI might not even be in C++).

Board has two Players, each Player has 16 Pieces, each Piece knows how to move?

- board.getState() gives state of board as a string or whatnot.
- board.move(player, pos1, pos2)
-- Check for Check, Checkmate, Stalemate.
