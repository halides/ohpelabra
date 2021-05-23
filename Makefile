CC = g++
CFLAGS = -std=c++11 -Wpedantic

all: qchess-srv.cpp piece.cpp player.cpp board.cpp
	$(CC) $(CFLAGS) -o qchess-srv qchess-srv.cpp piece.cpp player.cpp board.cpp

clean: 
	$(RM) qchess
