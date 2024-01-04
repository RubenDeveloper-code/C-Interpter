#ifndef __PRE_FGETCH_H__
#define __PRE_FGETCH_H__

#include <stdio.h>

int ffgetc(FILE *stream);
void skipComments(FILE *stream, char *token, char *prevToken);
void manageSpaces(FILE *stream, char *token, char *prevToken);

#endif
