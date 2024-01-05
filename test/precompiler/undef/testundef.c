#include "../../../include/precompiler/precompiler.h"

int main() {
      char *files[] = {"test/precompiler/undef/fortest/main.c"};
      return precompileAll(files, 1, "test/precompiler/undef/results/");
}
