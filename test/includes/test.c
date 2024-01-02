#include "../../include/precompiler.h"

int main() {
      char *files[] = {"test/includes/fortest/main.c",
                       "test/includes/fortest/res.c",
                       "test/includes/fortest/sum.c"};
      precompileAll(files, 3, "test/includes/results/");
}
