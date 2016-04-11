CC = g++
CFLAGS = -g -Wall

all: test.cpp
	$(CC) $(CFLAGS) -o test.out test.cpp

clean:
	$(RM) test.out
