CC = g++

CFLAGS = -Wall -std=c++14 -c
LFLAGS = -Wall -std=c++14

DEBUG = -g

OBJS = bin/lexer.o

metalc: src/main.cpp $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG) src/main.cpp $(OBJS) -o bin/metalc

bin/lexer.o: src/lexer.cpp src/lexer.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/lexer.cpp -o bin/lexer.o
