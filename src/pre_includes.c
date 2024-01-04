#include "../include/pre_includes.h"
#include "../include/pre_skeleton.h"
#include "../include/precompiler.h"

#include <stdlib.h>

// namefile>
char *getIncludeFile(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while ((*ptr = ffgetc(stream)) != TOKENS.INCLUDE_FIELD_CLOSED &&
             *ptr != TOKENS.QUOTES)
            ptr++;
      if (*ptr != TOKENS.INCLUDE_FIELD_CLOSED && *ptr != TOKENS.QUOTES) {
            reportPrecompileSyntaxError(nLines, token);
      }
      *ptr = TOKENS.ZERO_END;
      return token;
}

// namefile.h || el archivo se obtiene de donde este el .c relativo a este...
int includeFile(char *file, FILE *stream_out, char *path_src) {
      enum STATUS status = SUCCESS;
      char *filepath = malloc(sizeof(char) * BUFFSIZE);
      strcpy(filepath, path_src);
      strcat(filepath, file);
      FILE *include_stream = fopen(filepath, "r");
      status = precompile(include_stream, path_src);
      free(file);
      free(filepath);
      fclose(include_stream);
      return status;
}
