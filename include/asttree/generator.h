#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "../../include/asttree/nodes.h"
#include <stdio.h>

extern struct SuperNode *GLOBAL_NODE;

void *generateFile(char *file);
char *getLine(FILE *STREAM);
void generateNode(char *line);
int nodeType(char *token);

void *genDeclNode(enum TypeConstNode td, char *line);
void *genDefNode(char *line, enum TypeConstNode td, char *nameVar);
void *genValueNode(enum TypeConstNode td, char *line,
                   enum TypeNode *typeNodeRes);

void *genBinOperationNode(char *line, char *leftVal, enum TypeConstNode td);
int getOpe(char *token);

void *genGenericNode(enum TypeNode type, void *node);

enum TypeNode filterTypeNode(char *token);
enum TypeBinaryNode filterTypeNodeBin(char *line);
int isTypeData(char *token);
void addtoGlobalNode(void *Node);

#endif
