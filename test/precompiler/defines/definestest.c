#include "../../../include/precompiler/precompiler.h"
#include <stdio.h>

int main() {
      char *files[] = {"test/precompiler/defines/fortest/main.c"};
      int status = precompileAll(files, 1, "test/precompiler/defines/results/");
      printf("status; %i", status);
      return status;
}
