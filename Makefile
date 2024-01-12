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
#si algo no funca es prorque no estas compilando el untils auauau

ALL_AST_SRC = src/asttree/*


tests: testIncludes testDefines testConditions testUndef

TEST_INCLUDES_DIR = test/precompiler/includes
testIncludes:
	@gcc $(ALL_PRECOMPILER_SRC) $(TOKENS) $(TEST_INCLUDES_DIR)/test.c -o $(TEST_INCLUDES_DIR)/includes_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/includes/test.sh


TEST_DEFINES_DIR = test/precompiler/defines
testDefines:
	@gcc $(ALL_PRECOMPILER_SRC) $(TOKENS) $(TEST_DEFINES_DIR)/definestest.c -o $(TEST_DEFINES_DIR)/defines_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/defines/definestest.sh

TEST_CONDITIONS_DIR = test/precompiler/conditions
testConditions:
	@gcc $(ALL_PRECOMPILER_SRC) $(STATUSCHECK) $(TOKENS) $(TEST_CONDITIONS_DIR)/conditionstest.c -o $(TEST_CONDITIONS_DIR)/conditions_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/conditions/conditiontest.sh

TEST_UNDEF_DIR = test/precompiler/undef
testUndef:
	@gcc $(ALL_PRECOMPILER_SRC) $(STATUSCHECK) $(TOKENS) $(TEST_UNDEF_DIR)/testundef.c -o $(TEST_UNDEF_DIR)/undef_test.o -I $(INCLUDE) -g -Wall
	@test/precompiler/undef/testundef.sh

TEST_DECL_DIR = test/astTree/declare
testASTDecl:
	@gcc $(ALL_AST_SRC) $(TOKENS) $(TEST_DECL_DIR)/testdecl.c -o $(TEST_DECL_DIR)/decl_test.o -I $(INCLUDE) -g -Wall
	./test/astTree/declare/decl_test.o

