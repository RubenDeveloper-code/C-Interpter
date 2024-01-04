SRC = src/
INCLUDE = include/
CC = gcc
CFLAGS = -g -Wall
OUT = bin/rc
BIN = bin/
TESTS = test/
TESTSBIN = test/bin/

ALL_PRECOMPILER_SRC = src/precompiler.c src/pre_conditional.c src/pre_defines.c src/pre_fgetc.c src/pre_includes.c src/pre_utils.c src/tokens.c
STATUSCHECK = src/status.c
TEST_INCLUDES_DIR = test/includes

tests: testIncludes testDefines

testIncludes:
	@gcc $(ALL_PRECOMPILER_SRC) $(STATUSCHECK) $(TEST_INCLUDES_DIR)/test.c -o $(TEST_INCLUDES_DIR)/includes_test.o -I $(INCLUDE) -g -Wall
	@test/includes/test.sh


TEST_DEFINES_DIR = test/defines
testDefines:
	@gcc $(ALL_PRECOMPILER_SRC) $(STATUSCHECK) $(TEST_DEFINES_DIR)/definestest.c -o $(TEST_DEFINES_DIR)/defines_test.o -I $(INCLUDE) -g -Wall
	@test/defines/definestest.sh


