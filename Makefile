CC = g++
CFLAGS = -g -Wall

all: chess.cpp piece.cpp player.cpp board.cpp
	$(CC) $(CFLAGS) -o chess chess.cpp

clean: 
	$(RM) chess
