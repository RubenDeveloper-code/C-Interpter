#include "../../include/asttree/genTree.h"
#include "../../include/asttree/genNodes.h"
#include "../../include/tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFNODES 2048
#define BUFFSIZE 2048

struct SuperNode *GLOBAL_NODE;
struct SuperNode *ptrCurrentSuperNode;
struct SuperNode **depthCurrentSuperNode;

void *generateFile(char *file) {
      struct Node *genericNode = malloc(sizeof(struct Node));
      GLOBAL_NODE = malloc(sizeof(struct SuperNode));
      GLOBAL_NODE->nodes = malloc(sizeof(void *) * BUFNODES);
      ptrCurrentSuperNode = GLOBAL_NODE;
      depthCurrentSuperNode = malloc(sizeof(struct SuperNode) * BUFNODES);
      *++depthCurrentSuperNode = GLOBAL_NODE;
      FILE *STREAM = fopen(file, "r");
      if (STREAM == NULL)
            return NULL;
      char *line;
      do {
            line = getLine(STREAM);
            generateNode(line);
      } while (line[0] != TOKENS.ZERO_END);
      genericNode->type = SUPERNODE;
      genericNode->node = GLOBAL_NODE;
      fclose(STREAM);
      return genericNode;
}

char *getLine(FILE *STREAM) {
      char *line = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_line = line, token;
      while ((token = fgetc(STREAM)) != TOKENS.END_LINE &&
             token != TOKENS.OPEN_KEY && token != TOKENS.CLOSED_KEY &&
             token != EOF) {
            *ptr_line++ = token;
      }
      if (token != EOF)
            *ptr_line++ = token;
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
      return strdup(final_line);
}
