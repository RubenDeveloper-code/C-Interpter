#include "../include/status.h"
#include <stdio.h>
#include <stdlib.h>

// la linea se calculara alla, pa que coincida
void reportFileError(int nLine, char *file) {
      printf("Error line: %i Line, File: %s, no exists\n", nLine, file);
      exit(FILE_NOT_EXISTS);
}

void reportPrecompileSyntaxError(int nLine, char *extraInfo) {
      printf("Error line; %i %s\n", nLine, extraInfo);
      exit(SYNTAX_ERROR);
}
