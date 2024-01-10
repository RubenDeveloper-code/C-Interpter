#include "../../include/asttree/graphicTree.h"
#include "../../include/asttree/generator.h"
#include <stdio.h>

void genTree(void *fatherNode, char *outFile) {
      if (fatherNode != NULL) {
            FILE *out = fopen(outFile, "w");
            start(fatherNode, out);
      } else {
            printf("nodo padre vacion meco");
      }
}
void start(void *node, FILE *STREAM_OUT) { while () }
