#include "../../include/asttree/generator.h"
#include "../../include/asttree/astTokens.h"
#include "../../include/asttree/declares.h"
#include "../../include/asttree/nodes.h"
#include "../../include/tokens.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 2048

char advfgetc(FILE *STREAM) {
      char token;
      while ((token = fgetc(STREAM)) == TOKENS.SPACE)
            ;
      return token;
}
