#include "../include/untils.h"
#include "../include/tokens.h"
#include <stdio.h>
#include <string.h>

int isBetweenQuotes(char *token, int lenght_token, char *line) {
      char *pos = token;
      char *line_ptr = line;
      int startQ = 0, endQ = 0;
      while ((pos = strrchr(line_ptr, TOKENS.QUOTES)) != NULL) {
            startQ = !startQ;
            line_ptr = pos + 1;
      }
      line_ptr = token + lenght_token;
      while ((pos = strchr(line_ptr, TOKENS.QUOTES)) != NULL) {
            endQ = !endQ;
            line_ptr = pos + 1;
      }
      return startQ && endQ;
}
