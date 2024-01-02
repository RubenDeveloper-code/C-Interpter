#include "../include/precompiler.h"
#include <stdio.h>

int main() {
      char *files[] = {"test.c"};
      printf("0 es succes: %i", precompileAll(files, 1, "./"));

      testVariables();
}
