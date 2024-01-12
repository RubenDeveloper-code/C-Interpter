#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048
#define GETT 0
#define LEND 1

char *getToken(char *line, int typeRead, int indexStart) {
      static int offset = 0;
      char *token = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_line = line + offset;
      char *ptr;
      if (*line == TOKENS.SPACE)
            ptr_line++;
      do {
            ptr = token;
            while ((isalnum(*ptr++ = *ptr_line) ||
                    *ptr_line == TOKENS.UNDERSCORE)) {
                  ptr_line++;
            }
      } while (typeRead == LEND && --indexStart >= 0);
      *ptr = TOKENS.ZERO_END;
      if (typeRead == GETT)
            offset = strlen(line) - strlen(ptr_line);
      return token;
}

int getNTokens(char *line) {
      char *ptr_line = line;
      int cont = 0;
      while (*line++ == TOKENS.SPACE) {
            cont++;
      }
      return cont + 1;
}

char *getNextToken(char *line) { return getToken(line, GETT, 0); }
char *lendNextToken(char *line) { return getToken(line, LEND, 0); }
char *lendFirstToken(char *line) { return getToken(line, LEND, 0); }
char *lendToken(char *line, int index) { return getToken(line, LEND, index); }
char *lendLastToken(char *line) {
      return getToken(line, LEND, getNTokens(line));
}
