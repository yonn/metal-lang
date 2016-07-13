CC = g++

CFLAGS = -Wall -Wextra -std=c++14 -c
LFLAGS = -Wall -Wextra -std=c++14

DEBUG = -g

OBJS = bin/metal.o bin/parser.o bin/expression.o bin/lexer.o bin/error.o

metalc: src/main.cpp $(OBJS)
	$(CC) $(LFLAGS) $(DEBUG) src/main.cpp $(OBJS) -o bin/metalc

bin/metal.o: src/metal.cpp src/metal.hpp src/lexer.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/metal.cpp -o bin/metal.o

bin/parser.o: src/parser.cpp src/parser.hpp src/lexer.hpp src/expression.hpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/parser.cpp -o bin/parser.o

bin/expression.o: src/expression.cpp src/expression.hpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/expression.cpp -o bin/expression.o

bin/lexer.o: src/lexer.cpp src/lexer.hpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/lexer.cpp -o bin/lexer.o

bin/error.o: src/error.cpp src/error.hpp
	$(CC) $(CFLAGS) $(DEBUG) src/error.cpp -o bin/error.o -Wno-varargs
