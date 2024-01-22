#ifndef __GEN_NODES_H__
#define __GEN_NODES_H__

#include "nodes.h"

extern struct SuperNode *GLOBAL_NODE;
void *genBinOperationNode(char *line, char *leftVal, enum TypeConstNode td);
void *genDeclNode(enum TypeConstNode td, char *line);
void *genDefNode(char *line, enum TypeConstNode td, char *nameVar);
void *genValueNode(enum TypeConstNode td, char *line);
void *genGenericNode(enum TypeNode type, void *node);
void *genConditionalNode(char *line);
void *genIfNode(char *line);
void addtoGlobalNode(void *Node);
// renombrar
void generateNode(char *line);
#endif
