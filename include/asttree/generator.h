#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "../../include/asttree/nodes.h"
#include <stdio.h>

enum typedata { TYPE_INT, TYPE_CHAR, TYPE_FLOAT };

void *generateFile(char *file);
char *getLine(FILE *STREAM);
void *generateNode(char *line);
int nodeType(char *token);
void *genDeclNode(char *line);
enum TypeNode filterTypeNode(char *token);
enum TypeBinaryNode filterTypeNodeBin(char *line);
int isTypeData(char *token);

#endif
