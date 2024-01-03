SRC = src/
INCLUDE = include/
CC = gcc
CFLAGS = -g -Wall
OUT = bin/rc
BIN = bin/
TESTS = test/
TESTSBIN = test/bin/

PRECOMPILER = src/precompiler.c
STATUSCHECK = src/status.c
TEST_INCLUDES_DIR = test/includes

tests: testIncludes testDefines

testIncludes:
	@gcc $(PRECOMPILER) $(STATUSCHECK) $(TEST_INCLUDES_DIR)/test.c -o $(TEST_INCLUDES_DIR)/includes_test.o -I $(INCLUDE) -g -Wall 2> /dev/null
	@test/includes/test.sh


TEST_DEFINES_DIR = test/defines
testDefines:
	@gcc $(PRECOMPILER) $(STATUSCHECK) $(TEST_DEFINES_DIR)/definestest.c -o $(TEST_DEFINES_DIR)/defines_test.o -I $(INCLUDE) -g -Wall 2> /dev/null
	@test/defines/definestest.sh


