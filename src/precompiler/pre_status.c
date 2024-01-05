#include "../../include/precompiler/pre_status.h"
#include <stdio.h>
#include <stdlib.h>

int nLines = 0;
const char *ERRORS[] = {"", "syntax error %s in line %i",
                        "file: %s not exists %i",
                        "file: %s included in line: %i no exists",
                        "Variable: %s undefined in line %i not exists"};

void reportFatalError(int nLine, enum ERROR ERROR_CODE, char *extra_info) {
      printf(ERRORS[ERROR_CODE], extra_info, nLine);
      exit(ERROR_CODE);
}
