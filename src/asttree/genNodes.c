#include "../../include/asttree/genNodes.h"
#include "../../include/asttree/declares.h"
#include "../../include/asttree/filters.h"
#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include <stdlib.h>
#include <string.h>
#define BUFNODES 2048
#include <ctype.h>

struct SuperNode *GLOBAL_NODE;

void generateNode(char *line) {
      char *firstToken = getNextToken(line), *token = firstToken;
      while (*token != TOKENS.ZERO_END && *token != TOKENS.END_LINE &&
             *token != TOKENS.OPEN_KEY) {
            if (_nodeType(token) == BINARYNODE) {
                  enum TypeBinaryNode typeBinNode = _typeNodeBin(line);
                  if (typeBinNode == DECL) {
                        addtoGlobalNode(
                            genDeclNode(_typeData(firstToken), line));
                  } else if (typeBinNode == DEF) {
                        addtoGlobalNode(
                            genDefNode(line, _typeData(firstToken), token));
                  } else if (typeBinNode == IF) {
                        addtoGlobalNode(genIfNode(line));
                  }
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
      getNextToken(line);
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
            rightope->type = td;
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

void *genIfNode(char *line) {
      struct SuperNode *bodyNode = malloc(sizeof(struct SuperNode));
      struct BinaryNode *ifNode = malloc(sizeof(struct SuperNode));
      bodyNode->type = BODY;
      bodyNode->nodes = malloc(sizeof(struct Node) * BUFNODES);
      bodyNode->contNodes = 0;
      ifNode->type = IF;
      ifNode->left = genConditionalNode(line);
      ifNode->right = genGenericNode(SUPERNODE, bodyNode);
      return genGenericNode(BINARYNODE, ifNode);
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

void *genGenericNode(enum TypeNode type, void *node) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      genericNode->type = type;
      genericNode->node = node;
      return genericNode;
}
void addtoGlobalNode(void *Node) {
      GLOBAL_NODE->nodes[GLOBAL_NODE->contNodes++] = Node;
}
