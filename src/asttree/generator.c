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

int generateFile(char *file) {
      FILE *STREAM = fopen(file, "r");
      if (file == NULL)
            return -1;
      char *line;
      do {
            line = getLine(STREAM);

      } while (line[0] != TOKENS.ZERO_END);
      return 1;
}

void *generateLine(char *line) {
      char *token = getNextToken(line);
      // filtro y depende lo que retorne creamos el nodo
}

int nodeType(char *token) {}

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
      // ya se yase, si conosco los || pero and viendo que pedo
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
      while ((token = fgetc(STREAM)) != TOKENS.END_LINE) {
            *ptr_line++ = token;
      }
      *ptr_line = TOKENS.ZERO_END;
      char *final_line = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_final_line = final_line;
      ptr_line = line;
      while (*ptr_line != EOF) {
            if (*ptr_line == TOKENS.SPACE) {
                  if (isBetweenQuotes(ptr_line, 1, line)) {
                        *ptr_final_line++ = *ptr_line++;
                  }
            } else if (*ptr_line != TOKENS.JUMP_LINE) {
                  *ptr_final_line++ = *ptr_line++;
            }
      }
      *ptr_final_line = TOKENS.ZERO_END;
      return ptr_final_line;
}
