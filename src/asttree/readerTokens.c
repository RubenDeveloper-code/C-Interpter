#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048
#define GETT 0
#define LEND 1

char *getToken(char *line, int typeRead, int indexStart, int ofs) {
      static int offset = 0;
      if (ofs == -1) {
            offset = 0;
            return NULL;
      }
      char *token = malloc(sizeof(char) * BUFFSIZE);
      char *ptr_line = line + offset;
      char *ptr;
      if (*line == TOKENS.SPACE)
            ptr_line++;
      do {
            ptr = token;
            while (
                (isalnum(*ptr = *ptr_line) || *ptr_line == TOKENS.UNDERSCORE)) {
                  ptr_line++;
                  ptr++;
            }
      } while (typeRead == LEND && --indexStart >= 0);
      if (*(ptr - 1) == TOKENS.END_LINE)
            offset = 0;
      *ptr = TOKENS.ZERO_END;
      if (typeRead == GETT)
            offset = strlen(line) - strlen(ptr_line);
      return token;
}

void freeOffset() { getToken(NULL, 0, 0, -1); }

int getNTokens(char *line) {
      char *ptr_line = line;
      int cont = 0;
      while (*ptr_line++ == TOKENS.SPACE) {
            cont++;
      }
      return cont + 1;
}

char *getNextToken(char *line) { return getToken(line, GETT, 0, 0); }
char *lendNextToken(char *line) { return getToken(line, LEND, 0, 0); }
char *lendFirstToken(char *line) { return getToken(line, LEND, 0, 0); }
char *lendToken(char *line, int index) {
      return getToken(line, LEND, index, 0);
}
char *lendLastToken(char *line) {
      return getToken(line, LEND, getNTokens(line), 0);
}
