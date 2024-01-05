#include "../../include/precompiler/pre_fgetc.h"
#include "../../include/precompiler/pre_skeleton.h"
#include "../../include/precompiler/precompiler.h"

int ffgetc(FILE *stream) {
      static char prevToken;
      char token = fgetc(stream);
      skipComments(stream, &token, &prevToken);
      manageSpaces(stream, &token, &prevToken);
      if (token == TOKENS.END_LINE) {
            nLines++;
      }
      prevToken = token;
      return token;
}

// simple y multilinea...
void skipComments(FILE *stream, char *token, char *prevToken) {
      if (*token == TOKENS.SLASH && *prevToken == TOKENS.SLASH) {
            while ((*token = fgetc(stream)) != TOKENS.END_LINE)
                  ;
            funputc(stream_out);
            *token = fgetc(stream);
      } else if (*prevToken == TOKENS.SLASH && *token == TOKENS.ASTERISK) {
            *prevToken = *token;
            while ((*token = fgetc(stream)) != EOF) {
                  if (*token == TOKENS.SLASH && *prevToken == TOKENS.ASTERISK)
                        break;
                  *prevToken = *token;
            }
            *token = fgetc(stream);
            funputc(stream_out);
      }
}

void manageSpaces(FILE *stream, char *token, char *prevToken) {
      if (*token == TOKENS.SPACE) {
            while ((*token = fgetc(stream)) == TOKENS.SPACE)
                  ;
            if (((isalnum(*token) || *token == TOKENS.UNDERSCORE) &&
                 (isalnum(*prevToken) || *prevToken == TOKENS.UNDERSCORE))) {
                  ungetc(*token, stream);
                  *token = TOKENS.SPACE;
            }
      }
}
