SRC = src/
INCLUDE = include/
CC = gcc
CFLAGS = -g -Wall
OUT = bin/rc
BIN = bin/
TESTS = test/
TESTSBIN = test/bin/

all:
	$(CC) -o $(OUT) $(CFLAGS) -I $(INCLUDE) -c $(SRC)*.c


readerTest: 
	@$(CC) -o $(BIN)readerbin.o -c $(SRC)reader.c -I $(INCLUDE) $(CFLAGS)
	@$(CC) -o $(TESTSBIN)readertest.o -c  $(TESTS)readertest.c $(CFLAGS)
	@$(CC) -o $(TESTSBIN)reader $(BIN)readerbin.o $(TESTSBIN)readertest.o $(CFLAGS)
	@chmod +x $(TESTSBIN)reader
	@./$(TESTSBIN)reader
	@if [ $$? -eq 0 ]; then echo "reader pass"; else echo "reader not pass"; fi

tokenizerTest:
	@$(CC) -o $(BIN)tokenizer.o -c $(SRC)tokenizer.c -I $(INCLUDE) $(CFLAGS)
	@$(CC) -o $(TESTSBIN)tokenizertest.o -c  $(TESTS)tokenizertest.c $(CFLAGS)
	@$(CC) -o $(TESTSBIN)tokenizer $(BIN)tokenizer.o $(TESTSBIN)tokenizertest.o $(CFLAGS)
	@chmod +x $(TESTSBIN)tokenizer
	@./$(TESTSBIN)tokenizer

