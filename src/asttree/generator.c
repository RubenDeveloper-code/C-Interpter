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

void *generateFile(char *file) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      struct SuperNode *GLOBAL_NODE = malloc(sizeof(struct SuperNode));
      GLOBAL_NODE->nodes = malloc(sizeof(void *) * BUFFSIZE);
      FILE *STREAM = fopen(file, "r");
      if (file == NULL)
            return NULL;
      char *line;
      do {
            line = getLine(STREAM);
            GLOBAL_NODE->nodes[GLOBAL_NODE->contNodes++] = generateNode(line);
      } while (line[0] != TOKENS.ZERO_END);
      GLOBAL_NODE->contNodes--;
      genericNode->type = SUPERNODE;
      genericNode->node = GLOBAL_NODE;
      return genericNode;
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

// name;
void *genDeclNode(char *line) {
      char *name = strdup(getNextToken(line));
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

      return decl;
}

int nodeType(char *token) {
      if (isTypeData(token) != -1)
            return BINARYNODE;
      return -1;
}

enum TypeBinaryNode filterTypeNodeBin(char *line) {
      enum TypeBinaryNode nodetype = 0;
      if (isTypeData(lendFirstToken(line)) != -1) {
            if (lendToken(line, 2)[0] != TOKENS.EQUAL) {
                  nodetype = DECL;
            } else {
                  nodetype = DEF;
            }
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
