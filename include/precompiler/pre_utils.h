#ifndef __PRE_UTILS_H__
#define __PRE_UTILS_H__

#include <stdio.h>

char *ffgetcUntil(FILE *stream, char limit);
void funputc(FILE *stream);
int isBetweenQuotes(char *token, int lenght, char *line);

#endif
