CC = g++
CFLAGS = -g -Wall

all: qchess.cpp piece.cpp player.cpp board.cpp
	$(CC) $(CFLAGS) -o qchess qchess.cpp

clean: 
	$(RM) qchess
