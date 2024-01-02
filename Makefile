SRC = src/
INCLUDE = include/
CC = gcc
CFLAGS = -g -Wall
OUT = bin/rc
BIN = bin/
TESTS = test/
TESTSBIN = test/bin/

testIncludes:
	@rm test/includes/results/*
	@gcc src/precompiler.c test/includes/test.c -o test/includes/includes_test.o -I include -g -Wall 2> /dev/null
	@./test/includes/includes_test.o > /dev/null
	@for file in test/includes/results/*.pre; do \
		mv "$$file" "$${file%.pre}.c";\
		done
	
	@gcc -fsyntax-only test/includes/results/*.c 

