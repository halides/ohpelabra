CC = g++-4.9
CFLAGS = -g -Wall -std=c++14 -pedantic

all: qchess.cpp piece.cpp player.cpp board.cpp
	$(CC) $(CFLAGS) -o qchess qchess.cpp piece.cpp player.cpp board.cpp

clean: 
	$(RM) qchess
