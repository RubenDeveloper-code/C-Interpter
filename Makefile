SRC = src/
INCLUDE = include/
CC = gcc
CFLAGS = -g -Wall
OUT = bin/rc
BIN = bin/
TESTS = test/
TESTSBIN = test/bin/

ALL_PRECOMPILER_SRC = src/precompiler/precompiler.c \
		      src/precompiler/pre_conditional.c\
		      src/precompiler/pre_defines.c\
		      src/precompiler/pre_fgetc.c\
		      src/precompiler/pre_includes.c\
		      src/precompiler/pre_utils.c\
		      src/precompiler/pre_tokens.c\
		      src/precompiler/pre_status.c
TOKENS = src/tokens.c

UNTILS = src/untils.c

ALL_AST_SRC = src/asttree/*.c


tests: testIncludes testDefines testConditions testUndef

TEST_INCLUDES_DIR = test/precompiler/includes
testIncludes:
	@gcc $(ALL_PRECOMPILER_SRC) $(UNTILS) $(TOKENS) $(TEST_INCLUDES_DIR)/test.c -o $(TEST_INCLUDES_DIR)/includes_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/includes/test.sh


TEST_DEFINES_DIR = test/precompiler/defines
testDefines:
	@gcc $(ALL_PRECOMPILER_SRC) $(UNTILS) $(TOKENS) $(TEST_DEFINES_DIR)/definestest.c -o $(TEST_DEFINES_DIR)/defines_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/defines/definestest.sh

TEST_CONDITIONS_DIR = test/precompiler/conditions
testConditions:
	@gcc $(ALL_PRECOMPILER_SRC) $(STATUSCHECK) $(UNTILS) $(TOKENS) $(TEST_CONDITIONS_DIR)/conditionstest.c -o $(TEST_CONDITIONS_DIR)/conditions_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/conditions/conditiontest.sh

TEST_UNDEF_DIR = test/precompiler/undef
testUndef:
	@gcc $(ALL_PRECOMPILER_SRC) $(STATUSCHECK) $(UNTILS) $(TOKENS) $(TEST_UNDEF_DIR)/testundef.c -o $(TEST_UNDEF_DIR)/undef_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/undef/testundef.sh

TEST_DECL_DIR = test/astTree/treeGen
testASTDecl:
	@gcc $(ALL_AST_SRC) $(TOKENS) $(UNTILS) $(TEST_DECL_DIR)/testtree.c -o $(TEST_DECL_DIR)/tree_test.o -I $(INCLUDE) -g -Wall -lssl -lcrypto
	@$(TEST_DECL_DIR)/seetree.sh

TEST_READER_TOKENS_DIR = test/astTree/readerTokens
testTokenReader:
	@gcc $(TOKENS) src/asttree/readerTokens.c $(TEST_READER_TOKENS_DIR)/main.c -o $(TEST_READER_TOKENS_DIR)/readertest.o -I $(INCLUDE) -g -Wall
	./test/astTree/readerTokens/readertest.o


