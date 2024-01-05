#include "../../../include/precompiler/precompiler.h"
#include <stdlib.h>

int main() {
      char *files[] = {"test/precompiler/includes/fortest/main.c",
                       "test/precompiler/includes/fortest/res.c",
                       "test/precompiler/includes/fortest/sum.c"};
      return precompileAll(files, 3, "test/precompiler/includes/results/");
}
