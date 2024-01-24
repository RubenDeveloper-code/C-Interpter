#ifndef __GEN_NODES_H__
#define __GEN_NODES_H__

#include "nodes.h"

extern struct SuperNode *GLOBAL_NODE;
extern struct SuperNode *ptrCurrentSuperNode;
extern struct SuperNode **depthCurrentSuperNode;
void *genBinOperationNode(char *line, char *leftVal, enum TypeConstNode td);
void *genDeclNode(enum TypeConstNode td, char *line);
void *genDefNode(char *line, enum TypeConstNode td, char *nameVar);
void *genValueNode(enum TypeConstNode td, char *line);
void *genGenericNode(enum TypeNode type, void *node);
void *genConditionalNode(char *line);
void *genIfNode(char *line, struct SuperNode **IfScope,
                struct SuperNode **ElseScope);
void *genLoopNode(char *line, struct SuperNode **scope);
// for(int i = 0; i < 10; i++){
// }
void *genForNode(char *line, struct SuperNode **scopeFor);
void addtoCurrentSuperNode(void *Node);

void changeToNewScope(struct SuperNode *newScope);
void goBackScope();
// renombrar
void generateNode(char *line);
void initSuperNode(struct SuperNode **sp, enum TypeSuperNode type);
#endif
