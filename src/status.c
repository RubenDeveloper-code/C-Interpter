#include "../include/status.h"
#include <stdio.h>

// la linea se calculara alla, pa que coincida
void reportFileError(int nLine, char *file) {
      printf("Error line: %i Line, File: %s, no exists\n", nLine, file);
}

void reportPrecompileSyntaxError(int nLine, char *extraInfo) {
      printf("Error line; %i %s\n", nLine, extraInfo);
}
