#include "../include/pre_conditional.h"
#include "../include/pre_defines.h"
#include "../include/pre_skeleton.h"

int applyIsdef(FILE *stream, int ifn) {
      int exists = evaluateIsdef(stream);
      if (!exists) {
            char c;
            while ((c = fgetc(stream)) != EOF) {
                  if (c == TOKENS.PRECOMPILE_ORDER) {
                        char *token_ = malloc(BUFFSIZE * sizeof(char));
                        char *ptr = token_;
                        while (isalnum(*ptr = ffgetc(stream)))
                              ptr++;
                        *ptr = TOKENS.ZERO_END;
                        if (strcmp(token_, TOKENS.ENDIF))
                              break;
                  }
            }
      } else {
            // ps else
      }
      return SUCCESS;
}

int evaluateIsdef(FILE *stream) {
      char *toEvaluate = malloc(sizeof(char) * BUFFSIZE);
      char *ptr = toEvaluate;
      while ((*ptr = ffgetc(stream))) {
            ptr++;
      }
      *ptr = TOKENS.ZERO_END;
      return existsVar(ptr);
}
