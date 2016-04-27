CC = g++
CFLAGS = -std=c++11 -Wpedantic

all: qchess.cpp piece.cpp player.cpp board.cpp
	$(CC) $(CFLAGS) -o qchess qchess.cpp piece.cpp player.cpp board.cpp

clean: 
	$(RM) qchess
