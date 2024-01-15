#ifndef __READER_TOKENS_H__
#define __READER_TOKENS_H__

#include <stdio.h>

char *getNextToken(char *line);
char *lendNextToken(char *line);
char *lendLastToken(char *line);
char *lendFirstToken(char *line);
char *lendToken(char *line, int index);
void freeOffset();

#endif
