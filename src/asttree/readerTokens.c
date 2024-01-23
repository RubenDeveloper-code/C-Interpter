#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048
#define GETT 0
#define LEND 1
#define FREE 2

char *getToken(char *line, int typeRead, int indexStart, int ofs) {
      static int offset = 0;
      if (ofs == -1) {
            offset = 0;
            return NULL;
      }
      char *token;

      char *ptr_line = (typeRead == FREE) ? line : line + offset;
      char *ptr;
      do {
            ptr = token = malloc(sizeof(char) * BUFFSIZE);
            if (*ptr_line == TOKENS.SPACE)
                  ptr_line++;
            if (!isalnum(*ptr_line)) {
                  *ptr++ = *ptr_line++;
                  continue;
            }
            while ((isalnum(*ptr_line) || *ptr_line == TOKENS.UNDERSCORE)) {
                  *ptr++ = *ptr_line++;
            }
      } while (typeRead == FREE && --indexStart >= 0);
      if (*(ptr) == TOKENS.END_LINE) {
            offset = 0;
      }
      *ptr = TOKENS.ZERO_END;
      if (typeRead == GETT)
            offset = strlen(line) - strlen(ptr_line);
      return token;
}

void freeOffset() { getToken(NULL, 0, 0, -1); }

int getNTokens(char *line) {
      // int a=10;
      char *ptr_line = line;
      int cont = 0;
      if (*ptr_line == TOKENS.ZERO_END)
            return 0;
      do {
            if (*ptr_line == TOKENS.SPACE)
                  ptr_line++;
            if (!isalnum(*ptr_line)) {
                  ptr_line++;

            } else {
                  while (isalnum(*ptr_line) || *ptr_line == TOKENS.UNDERSCORE)
                        ptr_line++;
            }
            cont++;
      } while (*ptr_line != TOKENS.JUMP_LINE && *ptr_line != TOKENS.ZERO_END);
      printf("->end token index: %i\n", cont);
      return cont - 1;
}

char *getNextToken(char *line) { return getToken(line, GETT, 0, 0); }
char *lendNextToken(char *line) { return getToken(line, LEND, 0, 0); }
char *firstTokenIn(char *line) { return getToken(line, FREE, 0, 0); }
char *tokenIn(char *line, int index) { return getToken(line, FREE, index, 0); }
void skipNextToken(char *line, char *__FOR_PREVIEW_ONLY__) {
      getToken(line, GETT, 0, 0);
}
char *lastTokenIn(char *line) {
      return getToken(line, FREE, getNTokens(line), 0);
}
