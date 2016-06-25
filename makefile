CC = g++

CFLAGS = -Wall -std=c++14 -c
LFLAGS = -Wall -std=c++14

DEBUG = -g

metalc: src/main.cpp $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG) src/main.cpp $(OBJS) -o bin/metalc
