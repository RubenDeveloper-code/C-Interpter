SRC = src/
INCLUDE = include/
CC = gcc
CFLAGS = -g -Wall
OUT = bin/rc
BIN = bin/
TESTS = test/
TESTSBIN = test/bin/

testIncludes:
	@gcc src/precompiler.c test/includes/test.c -o test/includes/includes_test.o -I include -g -Wall 2> /dev/null
	@test/includes/test.sh

