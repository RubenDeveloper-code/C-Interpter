#include "../../include/asttree/generator.h"
#include "../../include/asttree/astTokens.h"
#include "../../include/asttree/declares.h"
#include "../../include/asttree/nodes.h"
#include "../../include/tokens.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048

int endLine = 0;
char *line;
struct Node *globalNode;
void *ptrNode;
int generateAST(char *file) {
      globalNode = malloc(sizeof(struct Node));
      ptrNode = globalNode;
      FILE *stream;
      if ((stream = fopen(file, "r")) == NULL)
            return 1;

      char *line;
      do {
            line = getLine(stream);
            processLine(line);
      } while (*line != TOKENS.ZERO_END);
      return 1;
}

char *getLine(FILE *STREAM) {
      line = malloc(sizeof(char) * BUFFSIZE);
      while ((*line++ = advfgetc(STREAM)) != TOKENS.END_LINE)
            ;
      return line;
}

int processLine(char *line) {
      do {
            void *tmp = generateNode(getNextToken());
            if (tmp == NULL)
                  return 1;
            globalNode->left = tmp;
            ptrNode = tmp;
      } while (!endLine);
      return 0;
}

void *generateNode(char *token) {
      enum NODES node_type = filterNode(token);
      void *node;
      switch (node_type) {
      case DECLVAR: {
            node = generateDclNode(SIMPLE);
            addDeclareVar(&node);
      }
      case DECLARRAY: {
            node = generateDclNode(ARRAY);
            addDeclareArray(&node);
      }
      case DECLFOO: {
            node = generateDclNode(FOO);
            addDeclareFoo(&node);
      }
      }
      return node;
}

enum NODES filterNode(char *token) {
      enum NODES node = -1;
      if (getType(token) != NONE)
            node = TYPE;
      char *next = getNextToken();
      if (node == TYPE && isalnum(next[0]) && next[0] == TOKENS.UNDERSCORE) {
            node = DECLVAR;
            if ()
      }
      next = getNextToken();
      if (node == DECLVAR && next[0] == TOKENS.BRACKET_OPEN) {
            node = DECLARRAY;
            // falta ver []={} [len] [][] ojo
      }
      if (node == DECLVAR && next[0] == TOKENS.OPEN_PARENTHESIS) {
            node = DECLFOO;
            // si no tiene args
      }
      return node;
}

// type <-/Dcl\-> name
void *generateDclNode(enum TYPE dcltype) {
      enum TYPES_DATA type_data = getType(getTokenByIndex(0));
      char *name = getTokenByIndex(1);
      struct Declare *node = malloc(sizeof(struct Declare));
      node->typedata = type_data;
      node->type = dcltype;
      node->name = name;
      return node;
}

enum TYPES_DATA getType(char *token) {
      if (strcmp(token, ASTTOKENS.TYPES[INT]) == 0)
            return INT;
      if (strcmp(token, ASTTOKENS.TYPES[CHAR]) == 0)
            return CHAR;
      if (strcmp(token, ASTTOKENS.TYPES[FLOAT]) == 0)
            return FLOAT;
      if (strcmp(token, ASTTOKENS.TYPES[VOID]) == 0)
            return VOID;
      return -1;
}

char *getTokenByIndex(int index) {
      char *ptr_line = line;
      char *token = malloc(sizeof(char) * BUFFSIZE);
      while (isalnum(*token++ = *ptr_line++) && index-- >= 0)
            ;
      if (*token - 1 == TOKENS.END_LINE)
            return EOF;
      *token = TOKENS.ZERO_END;
      return token;
}

char *getNextToken() {
      static int posLine = 0;
      const char *ptr_line = line + posLine;
      if (*ptr_line == TOKENS.END_LINE) {
            endLine = 1;
      }
      char *token = malloc(2048 * sizeof(char));
      while (isalnum(*token++ = *ptr_line++))
            ++posLine;
      if (*token - 1 == TOKENS.END_LINE)
            posLine = 0;
      *token = TOKENS.ZERO_END;
      return token;
}

char advfgetc(FILE *STREAM) {
      char token;
      while ((token = fgetc(STREAM)) == TOKENS.SPACE)
            ;
      return token;
}
