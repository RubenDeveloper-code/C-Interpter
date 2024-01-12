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

struct Node *generateFile(char *file) {
      struct Node *GLOBAL_NODE = malloc(sizeof(struct Node));
      GLOBAL_NODE->SuperNode.nodes = malloc(sizeof(void *) * BUFFSIZE);
      FILE *STREAM = fopen(file, "r");
      if (file == NULL)
            return NULL;
      char *line;
      do {
            line = getLine(STREAM);
            GLOBAL_NODE->SuperNode.nodes = generateNode(line);
            GLOBAL_NODE->SuperNode.nodes++;
      } while (line[0] != TOKENS.ZERO_END);
      return GLOBAL_NODE;
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
      return node;
}

// name;
void *genDeclNode(char *line) {
      char *name = strdup(getNextToken(line));
      struct Node *typeData = malloc(sizeof(struct Node));
      struct Node *nameData = malloc(sizeof(struct Node));
      struct Node *binNode = malloc(sizeof(struct Node));
      typeData->ConstNode.type = INT;
      typeData->ConstNode.VAL.INTEGER = INT;
      nameData->ConstNode.type = CHAR;
      nameData->ConstNode.VAL.STRING = name;
      binNode->BinaryNode.type = DECL;
      binNode->BinaryNode.left = typeData;
      binNode->BinaryNode.right = nameData;
      return binNode;
}

int nodeType(char *token) {
      if (isTypeData(token))
            return BINARYNODE;
      return -1;
}

enum TypeBinaryNode filterTypeNodeBin(char *line) {
      enum TypeBinaryNode nodetype = 0;
      if (isTypeData(lendFirstToken(line)) != 0) {
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
      return 0;
}

char *getLine(FILE *STREAM) {
      char *line = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_line = line, token;
      while ((token = fgetc(STREAM)) != EOF) {
            *ptr_line++ = token;
      }
      *ptr_line = TOKENS.ZERO_END;
      char *final_line = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_final_line = final_line;
      ptr_line = line;
      while (*ptr_line != TOKENS.ZERO_END) {
            /*
          if (*ptr_line == TOKENS.SPACE) {
                if (isBetweenQuotes(ptr_line, 1, line)) {
                      *ptr_final_line = *ptr_line;
                      ptr_final_line++;
                }
          } else*/
            if (*ptr_line != TOKENS.JUMP_LINE) {
                  *ptr_final_line = *ptr_line;
                  ptr_final_line++;
            }
            ptr_line++;
      }
      *ptr_final_line = TOKENS.ZERO_END;
      return final_line;
}
