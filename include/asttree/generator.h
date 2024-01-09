#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "../../include/asttree/nodes.h"
#include <stdio.h>

int generateAST(char *file);
char *getLine(FILE *STREAM);

int processLine(char *line);
char *getNextToken();

void *generateNode(char *token);

enum NODES filterNode(char *token);

void *generateDclNode(enum TYPE typedcl);

char *getTokenByIndex(int index);

enum TYPES_DATA getType(char *token);

char advfgetc(FILE *STREAM);

#endif
