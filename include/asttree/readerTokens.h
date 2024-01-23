#ifndef __READER_TOKENS_H__
#define __READER_TOKENS_H__

#include <stdio.h>

char *getNextToken(char *line);
char *lendNextToken(char *line);
char *lastTokenIn(char *line);
char *firstTokenIn(char *line);
char *tokenIn(char *line, int index);
void skipNextToken(char *line, char *__FOR_SYMBOLIC_PREVIEW_ONLY__);
void freeOffset();

#endif
