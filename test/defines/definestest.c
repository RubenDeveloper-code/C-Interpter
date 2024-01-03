#include "../../include/precompiler.h"
#include <stdio.h>

int main() {
      char *files[] = {"test/defines/fortest/main.c"};
      int status = precompileAll(files, 1, "test/defines/results/");
      printf("status; %i", status);
      return status;
}
