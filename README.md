# ohpelabra

## A quantum chess with C++

### Rules of the game

http://research.cs.queensu.ca/Parallel/QuantumChess/QuantumChess.html

Normal chess rules apply with the following changes:
- each piece (except the king) has in addition to it's normal value a randomly chosen quantum value from the collection of 8 pawns, 2 rooks, 2 knights, 2 bishops and 1 queen.
- when a player wants to move, he chooses a piece. that piece has a 50-50 chance of being the normal piece or the quantum piece for that move. the player has to move that piece and it automatically goes back to normal after the move.
- if a piece collapses into a type with no possible moves, then the player’s turn is over.
- the quantum value is not known by either player until a piece randomly collapses to a quantum piece.
- there is no "check" or "checkmate". the king is a piece that is captured as any other piece and this is a win condition.
- the king can be played into and left in check.
- castling is not allowed.
- there is no "en passant"-rule.
- a pawn reaching the last rank is promoted. this promotion is for it's current state.
- if a piece in quantum state on the far row is touched and revealed to be a pawn, it is promoted, but the promotion takes up the turn. the superimposed piece type is not affected.


(a piece in classical state with no legal moves cannot be chosen.) Personally I felt this a bit boring and left in the ability to play the lottery.


### Technical notes

gcc 4.9.2, using C++14. (g++-4.9 -g -Wall -std=c++14 -pedantic)

make && ./qchess

make clean

Some sort of MVC with a CLI (the CLI might not even be in C++).

Hours:
- 5.4 1h create repo
- 8.4 1h think about stuff, mod readme
- 11.4 4h basic structure, lots of reading up on C++
- 14.4 4h lots of progress, help from a friend
- 18.4 3h piece movement
- 19.4 3h collision, running into a bad bug
- 20.4 4h fixed bug (uninitialized variable), pawn movement implemented
- 21.4 7h all movements implemented, collision check ok, capturing pieces ok. another bad bug which was resolved (return value was a ref but then using it by value anyhow).
