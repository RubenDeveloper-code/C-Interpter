#include "../../../include/precompiler/precompiler.h"

int main() {
      char *files[2048] = {"test/precompiler/conditions/fortest/main.c"};
      return precompileAll(files, 1, "test/precompiler/conditions/results/");
}
