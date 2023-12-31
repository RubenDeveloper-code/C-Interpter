#include "../../include/precompiler/pre_utils.h"
#include "../../include/precompiler/pre_skeleton.h"
#include <stdio.h>
#include <stdlib.h>

void funputc(FILE *stream) {
      fseek(stream, -1, SEEK_END);
      ftruncate(fileno(stream), ftell(stream));
}

char *ffgetcUntil(FILE *stream, char limit) {
      char *word = malloc(sizeof(char) * BUFFSIZE);
      char *ptr = word;
      char token;
      while ((token = ffgetc(stream)) != limit && token != EOF) {
            *ptr++ = token;
      }
      *ptr = TOKENS.ZERO_END;
      return word;
}

int isBetweenQuotes(char *token, int lenght, char *line) {
      char *pos = token;
      char *line_ptr = line;
      int startQ = 0, endQ = 0;
      while ((pos = strrchr(line_ptr, TOKENS.QUOTES)) != NULL) {
            startQ = !startQ;
            line_ptr = pos + 1;
      }
      line_ptr = token + lenght;
      while ((pos = strchr(line_ptr, TOKENS.QUOTES)) != NULL) {
            endQ = !endQ;
            line_ptr = pos + 1;
      }
      printf("s:%i, e:%i\n", startQ, endQ);
      return startQ && endQ;
}
