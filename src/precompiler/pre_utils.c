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
