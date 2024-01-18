#include "../../include/asttree/generator.h"
#include "../../include/asttree/astTokens.h"
#include "../../include/asttree/declares.h"
#include "../../include/asttree/nodes.h"
#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include "../../include/untils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048
#define NONE -1

struct SuperNode *GLOBAL_NODE;

void *generateFile(char *file) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      GLOBAL_NODE = malloc(sizeof(struct SuperNode));
      GLOBAL_NODE->nodes = malloc(sizeof(void *) * BUFFSIZE);
      FILE *STREAM = fopen(file, "r");
      if (file == NULL)
            return NULL;
      char *line;
      do {
            line = getLine(STREAM);
            generateNode(line);
      } while (line[0] != TOKENS.ZERO_END);
      genericNode->type = SUPERNODE;
      genericNode->node = GLOBAL_NODE;
      return genericNode;
}

void addtoGlobalNode(void *Node) {
      GLOBAL_NODE->nodes[GLOBAL_NODE->contNodes++] = Node;
}

void generateNode(char *line) {
      char *firstToken = getNextToken(line), *token = firstToken;
      while (*token != TOKENS.ZERO_END && *token != TOKENS.END_LINE) {
            if (nodeType(token) == BINARYNODE) {
                  enum TypeBinaryNode typeBinNode = filterTypeNodeBin(line);
                  if (typeBinNode == DECL) {
                        addtoGlobalNode(
                            genDeclNode(isTypeData(firstToken), line));
                  } else if (typeBinNode == DEF) {
                        addtoGlobalNode(
                            genDefNode(line, isTypeData(firstToken), token));
                  }
            }
            token = getNextToken(line);
      }
      freeOffset();
}

// name;
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
      enum TypeNode typeNode = NONE;
      value = genValueNode(td, line, &typeNode);
      defbin->type = DEF;
      defbin->left = genGenericNode(CONSTNODE, var);
      defbin->right = value;

      return genGenericNode(BINARYNODE, defbin);
}

// Comprobacion de compatibilidad de tipos a la hora de interpretar
void *genValueNode(enum TypeConstNode td, char *line,
                   enum TypeNode *typeNodeRes) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      char *token = strdup(getNextToken(line));
      *typeNodeRes = CONSTNODE;
      if (isalpha(token[0])) {
            int testVar = existsVar(token);
            if (testVar != NONE) {
                  genericNode =
                      genGenericNode(CONSTNODE, &declaresVar[testVar]);
                  if (getOpe(lendNextToken(line)) != NONE) {
                        genericNode = genBinOperationNode(line, token, td);
                        *typeNodeRes = BINARYNODE;
                  } else {
                        return NULL;
                  }
            } else {
                  return NULL;
            }
      } else if (isdigit(token[0])) {
            struct ConstNode *node = malloc(sizeof(struct ConstNode));
            node->type = INT;
            node->value = token;
            genericNode = genGenericNode(CONSTNODE, node);
            if (getOpe(lendNextToken(line)) != NONE) {
                  genericNode = genBinOperationNode(line, token, td);
                  *typeNodeRes = BINARYNODE;
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

      enum TypeBinaryNode typeOp = getOpe(getNextToken(line));
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
      if (getOpe(lendNextToken(line)) != NONE) {
            opNode->right = genBinOperationNode(line, token, td);
      } else {
            opNode->right = genGenericNode(CONSTNODE, rightope);
      }
      return genGenericNode(BINARYNODE, opNode);
}

int getOpe(char *token) {
      if (token[0] == TOKENS.ADD)
            return ADD;
      if (token[0] == TOKENS.RES)
            return RES;
      if (token[0] == TOKENS.MULT)
            return MULT;
      if (token[0] == TOKENS.DIV)
            return DIV;
      return NONE;
}

void *genGenericNode(enum TypeNode type, void *node) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      genericNode->type = type;
      genericNode->node = node;
      return genericNode;
}

int nodeType(char *token) {
      // se preguntara por tokens
      return BINARYNODE;
}
// int a = c+b
enum TypeBinaryNode filterTypeNodeBin(char *line) {
      enum TypeBinaryNode nodetype = 0;
      if (lendToken(line, 0)[0] != TOKENS.EQUAL) {
            nodetype = DECL;
      } else {
            nodetype = DEF;
      }
      return nodetype;
}

int isTypeData(char *token) {
      if (strcmp(token, RESERVED_WORDS._INT_) == 0)
            return INT;
      if (strcmp(token, RESERVED_WORDS._CHAR_) == 0)
            return CHAR;
      if (strcmp(token, RESERVED_WORDS._FLOAT_) == 0)
            return FLOAT;
      return -1;
}

char *getLine(FILE *STREAM) {
      char *line = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_line = line, token;
      while ((token = fgetc(STREAM)) != TOKENS.END_LINE && token != EOF) {
            *ptr_line++ = token;
      }
      *ptr_line = TOKENS.ZERO_END;
      char *final_line = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_final_line = final_line;
      ptr_line = line;
      while (*ptr_line != TOKENS.ZERO_END) {
            if (*ptr_line != TOKENS.JUMP_LINE) {
                  *ptr_final_line = *ptr_line;
                  ptr_final_line++;
            }
            ptr_line++;
      }
      *ptr_final_line = TOKENS.ZERO_END;
      return final_line;
}
