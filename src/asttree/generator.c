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
            addtoGlobalNode(generateNode(line));
      } while (line[0] != TOKENS.ZERO_END);
      GLOBAL_NODE->contNodes--;
      genericNode->type = SUPERNODE;
      genericNode->node = GLOBAL_NODE;
      return genericNode;
}

void addtoGlobalNode(void *Node) {
      GLOBAL_NODE->nodes[GLOBAL_NODE->contNodes++] = Node;
}

void *generateNode(char *line) {
      char *token = getNextToken(line);
      void *node;
      if (nodeType(token) == BINARYNODE) {
            switch (filterTypeNodeBin(line)) {
            case DECL: {
                  node = genDeclNode(line);
                  break;
            }
            case DEF: {
                  int typedata = -1;
                  if ((typedata = isTypeData(token)) != -1) {
                        addtoGlobalNode(genDeclNode(line));
                  }
                  node = genDefNode(line, typedata);
                  break;
            }
            case IF: {
                  break;
            }
            case WHILE: {
                  break;
            }
            }
      }
      freeOffset();
      return node;
}
void *genDefNode(char *line, enum TypeConstNode typedata) {
      char *name = strdup(getNextToken(line));
      getNextToken(line);
      struct ConstNode *var = malloc(sizeof(struct ConstNode));
      struct ConstNode *value = malloc(sizeof(struct ConstNode));
      struct BinaryNode *defbin = malloc(sizeof(struct BinaryNode));

      struct Node *def = malloc(sizeof(struct Node));
      struct Node *left = malloc(sizeof(struct Node));
      struct Node *right = malloc(sizeof(struct Node));

      var->type = ACCESS_VAR;
      if (existsVar(name) != -1) {
            var->VAL.STRING = name;
      } else {
            // Syntax error
            return NULL;
      }
      left->type = CONSTNODE;
      left->node = var;

      value->type = typedata;
      value->VAL.STRING = strdup(getNextToken(line));
      right->type = CONSTNODE;
      right->node = value;

      defbin->type = DEF;
      defbin->left = left;
      defbin->right = right;

      def->type = BINARYNODE;
      def->node = defbin;

      return def;
}

// name;
void *genDeclNode(char *line) {
      char *name = strdup(lendNextToken(line));
      struct ConstNode *typeData = malloc(sizeof(struct ConstNode));
      struct ConstNode *nameData = malloc(sizeof(struct ConstNode));
      struct BinaryNode *dclNode = malloc(sizeof(struct BinaryNode));

      struct Node *decl = malloc(sizeof(struct Node));
      struct Node *left = malloc(sizeof(struct Node));
      struct Node *right = malloc(sizeof(struct Node));

      typeData->type = INT;
      typeData->VAL.INTEGER = INT;
      left->type = CONSTNODE;
      left->node = typeData;

      nameData->type = CHAR;
      nameData->VAL.STRING = name;
      right->type = CONSTNODE;
      right->node = nameData;

      dclNode->type = DECL;
      dclNode->left = left;
      dclNode->right = right;

      decl->type = BINARYNODE;
      decl->node = dclNode;

      addDeclareVar(nameData);
      return decl;
}

int nodeType(char *token) {
      if (isTypeData(token) != -1)
            return BINARYNODE;
      return -1;
}

enum TypeBinaryNode filterTypeNodeBin(char *line) {
      enum TypeBinaryNode nodetype = 0;
      char *temp = lendToken(line, 2);
      if (lendToken(line, 1)[0] != TOKENS.EQUAL) {
            nodetype = DECL;
      } else {
            nodetype = DEF;
      }
      return nodetype;
}

int isTypeData(char *token) {
      if (strcmp(token, RESERVED_WORDS._INT_) == 0)
            return TYPE_INT;
      if (strcmp(token, RESERVED_WORDS._CHAR_) == 0)
            return TYPE_CHAR;
      if (strcmp(token, RESERVED_WORDS._FLOAT_) == 0)
            return TYPE_FLOAT;
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
