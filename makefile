CC = g++

CFLAGS = -Wall -std=c++14 -c
LFLAGS = -Wall -std=c++14

DEBUG = -g

OBJS = bin/metal.o bin/lexer.o bin/error.o

metalc: src/main.cpp $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG) src/main.cpp $(OBJS) -o bin/metalc

bin/metal.o: src/metal.cpp src/metal.hpp src/lexer.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/metal.cpp -o bin/metal.o

bin/expression.o: src/expression.cpp src/expression.hpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/expression.cpp src/expression.hpp

bin/lexer.o: src/lexer.cpp src/lexer.hpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/lexer.cpp -o bin/lexer.o

bin/error.o: src/error.cpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/error.cpp -o bin/error.o -Wno-varargs
