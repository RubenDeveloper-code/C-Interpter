#include "../../include/precompiler.h"

int main() {
      char *files[2048] = {"test/conditions/fortest/main.c"};
      return precompileAll(files, 1, "test/conditions/results/");
}
