#include "../../include/asttree/genNodes.h"
#include "../../include/asttree/declares.h"
#include "../../include/asttree/filters.h"
#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include <stdlib.h>
#include <string.h>
#define BUFNODES 2048
#include <ctype.h>

struct SuperNode *firstCaseNewScope, *secondCaseNewScope;
void generateNode(char *line) {
      char *firstToken = getNextToken(line), *token = firstToken;
      while (*token != TOKENS.ZERO_END && *token != TOKENS.END_LINE) {
            // typebinNode ps ya no if es super
            enum TypeBinaryNode typeBinNode = _typeNodeBin(line, token);
            enum TypeSuperNode typeSuperNode = _typeSuperNode(line, token);
            if (typeBinNode != NONE) {
                  if (typeBinNode == DECL) {
                        addtoCurrentSuperNode(
                            genDeclNode(_typeData(firstToken), line));
                  } else if (typeBinNode == DEF) {
                        addtoCurrentSuperNode(
                            genDefNode(line, _typeData(firstToken), token));
                  } else if (typeBinNode == LOOP) {
                        addtoCurrentSuperNode(
                            genLoopNode(line, &firstCaseNewScope));
                  }
            } else if (typeSuperNode != NONE) {
                  if (typeSuperNode == IF) {
                        addtoCurrentSuperNode(genIfNode(
                            line, &firstCaseNewScope, &secondCaseNewScope));
                  } /* else if (typeSuperNode == FOR) {
                         addtoCurrentSuperNode(
                             genForNode(line, &firstCaseNewScope));
                   }*/
            } else if (token[0] == TOKENS.OPEN_KEY) {
                  changeToNewScope(firstCaseNewScope);
            } else if (token[0] == TOKENS.CLOSED_KEY) {
                  goBackScope();
            } else if (strcmp(token, RESERVED_WORDS._ELSE_) == 0) {
                  firstCaseNewScope = secondCaseNewScope;
            }
            token = getNextToken(line);
      }
      freeOffset();
}
void *genDeclNode(enum TypeConstNode td, char *line) {
      char *name = strdup(lendNextToken(line));
      struct ConstNode *typeData = malloc(sizeof(struct ConstNode));
      struct ConstNode *nameData = malloc(sizeof(struct ConstNode));
      struct BinaryNode *dclNode = malloc(sizeof(struct BinaryNode));

      typeData->type = TYPEDATA;
      typeData->value = malloc(1);
      typeData->value[0] = td + '0';

      nameData->type = VAR;
      nameData->value = name;

      dclNode->type = DECL;
      dclNode->left = genGenericNode(CONSTNODE, typeData);
      dclNode->right = genGenericNode(CONSTNODE, nameData);

      addDeclareVar(nameData);
      return genGenericNode(BINARYNODE, dclNode);
}

void *genDefNode(char *line, enum TypeConstNode td, char *nameVar) {
      char *name = nameVar;
      skipNextToken(line, "=");
      struct ConstNode *var = malloc(sizeof(struct ConstNode));
      struct Node *value = malloc(sizeof(struct Node));
      struct BinaryNode *defbin = malloc(sizeof(struct BinaryNode));

      var->type = VAR;
      if (existsVar(name) != -1) {
            var->value = strdup(name);
      } else {
            // Syntax error
            return NULL;
      }
      value = genValueNode(td, line);
      defbin->type = DEF;
      defbin->left = genGenericNode(CONSTNODE, var);
      defbin->right = value;

      return genGenericNode(BINARYNODE, defbin);
}

// Comprobacion de compatibilidad de tipos a la hora de interpretar
void *genValueNode(enum TypeConstNode td, char *line) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      char *token = strdup(getNextToken(line));
      if (isalpha(token[0])) {
            int testVar = existsVar(token);
            if (testVar != NONE) {
                  genericNode =
                      genGenericNode(CONSTNODE, &declaresVar[testVar]);
                  if (_operationType(lendNextToken(line)) != NONE) {
                        genericNode = genBinOperationNode(line, token, td);
                  }
            } else {
                  return NULL;
            }
      } else if (isdigit(token[0])) {
            struct ConstNode *node = malloc(sizeof(struct ConstNode));
            node->type = INT;
            node->value = token;
            genericNode = genGenericNode(CONSTNODE, node);
            if (_operationType(lendNextToken(line)) != NONE) {
                  genericNode = genBinOperationNode(line, token, td);
            }
      }
      return genericNode;
}

void *genIfNode(char *line, struct SuperNode **IfScope,
                struct SuperNode **ElseScope) {
      struct SuperNode *bodyNode = malloc(sizeof(struct SuperNode));
      struct SuperNode *bodyElseNode = malloc(sizeof(struct SuperNode));
      struct SuperNode *ifNode = malloc(sizeof(struct SuperNode));
      bodyNode->type = BODY;
      bodyNode->nodes = malloc(sizeof(struct Node) * BUFNODES);
      bodyNode->contNodes = 0;
      bodyElseNode->type = SECONDBODY;
      bodyElseNode->nodes = malloc(sizeof(struct Node) * BUFNODES);
      bodyElseNode->contNodes = 0;
      ifNode->type = IF;
      ifNode->nodes = malloc(sizeof(struct Node) * 3);
      ifNode->nodes[0] = genConditionalNode(line);
      ifNode->nodes[1] = genGenericNode(SUPERNODE, bodyNode);
      ifNode->nodes[2] = genGenericNode(SUPERNODE, bodyElseNode);
      ifNode->contNodes = 3;
      *IfScope = bodyNode;
      *ElseScope = bodyElseNode;
      return genGenericNode(SUPERNODE, ifNode);
}
// pa mas tarde el for
void *genForNode(char *line, struct SuperNode **scopeFor) {
      struct SuperNode *forNode = malloc(sizeof(struct SuperNode));
      struct SuperNode *body = malloc(sizeof(struct SuperNode));
      while (lendNextToken(line)[0] == TOKENS.OPEN_PARENTHESIS)
            skipNextToken(line, "(");
      forNode->nodes = malloc(sizeof(struct Node) * 4);
      char *tempType = lendNextToken(line);
      forNode->nodes[0] = genDeclNode(_typeData(tempType), line);
      forNode->nodes[1] =
          genDefNode(line, _typeData(tempType), getNextToken(line));
      forNode->nodes[2] = genConditionalNode(line);
      initSuperNode(&body, BODY);
      forNode->nodes[3] = genGenericNode(SUPERNODE, body);
      forNode->contNodes = 4;
      forNode->type = FOR;
      *scopeFor = body;
      return genGenericNode(SUPERNODE, forNode);
}

void *genConditionalNode(char *line) {
      char *startcondition;
      int parse;
      struct BinaryNode *conditionNodeBin = malloc(sizeof(struct BinaryNode));
      while ((startcondition = lendNextToken(line))[0] ==
             TOKENS.OPEN_PARENTHESIS)
            getNextToken(line);
      ;

      void *buf = genValueNode(INT, line);
      int condition = _conditional(getNextToken(line), line);
      if (condition != NONE) {
            conditionNodeBin->left = buf;
            conditionNodeBin->type = condition;
            conditionNodeBin->right = genConditionalNode(line);
      } else {
            return buf;
      }
      return genGenericNode(BINARYNODE, conditionNodeBin);
}

// +a...
void *genBinOperationNode(char *line, char *leftVal, enum TypeConstNode td) {
      struct BinaryNode *opNode = malloc(sizeof(struct BinaryNode));
      struct ConstNode *leftope = malloc(sizeof(struct ConstNode));
      struct ConstNode *rightope = malloc(sizeof(struct ConstNode));

      if (isdigit(leftVal[0])) {
            leftope->type = td;
      } else
            leftope->type = VAR;
      leftope->value = strdup(leftVal);

      enum TypeBinaryNode typeOp = _operationType(getNextToken(line));
      opNode->type = typeOp;
      char *token = getNextToken(line);
      if (isalpha(token[0])) {
            int testVar = existsVar(token);
            if (testVar != NONE) {
                  rightope = &declaresVar[testVar];
            } else {
                  // syntax error
                  return NULL;
            }
      } else if (isdigit(token[0])) {
            rightope->type = INT;
            rightope->value = token;
      } else {
            return NULL;
      }
      opNode->left = genGenericNode(CONSTNODE, leftope);
      if (_operationType(lendNextToken(line)) != NONE) {
            opNode->right = genBinOperationNode(line, token, td);
      } else {
            opNode->right = genGenericNode(CONSTNODE, rightope);
      }
      return genGenericNode(BINARYNODE, opNode);
}

void *genLoopNode(char *line, struct SuperNode **scope) {
      struct SuperNode *body = malloc(sizeof(struct SuperNode));
      struct BinaryNode *whileNode = malloc(sizeof(struct BinaryNode));
      initSuperNode(&body, BODY);
      whileNode->type = LOOP;
      whileNode->left = genConditionalNode(line);
      whileNode->right = genGenericNode(SUPERNODE, body);
      return genGenericNode(BINARYNODE, whileNode);
}

void initSuperNode(struct SuperNode **sp, enum TypeSuperNode type) {
      struct SuperNode *nsp = malloc(sizeof(struct SuperNode));
      nsp->type = type;
      nsp->nodes = malloc(sizeof(char) * BUFNODES);
      nsp->contNodes = 0;
      *sp = nsp;
}

void *genGenericNode(enum TypeNode type, void *node) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      genericNode->type = type;
      genericNode->node = node;
      return genericNode;
}
void addtoCurrentSuperNode(void *Node) {
      ptrCurrentSuperNode->nodes[ptrCurrentSuperNode->contNodes++] = Node;
}
void changeToNewScope(struct SuperNode *newScope) {
      *++depthCurrentSuperNode = newScope;
      ptrCurrentSuperNode = newScope;
}
void goBackScope() { ptrCurrentSuperNode = *--depthCurrentSuperNode; }
