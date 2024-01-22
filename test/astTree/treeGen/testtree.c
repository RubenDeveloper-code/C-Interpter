#include "../../../include/asttree/genTree.h"
#include "../../../include/asttree/graphicTree.h"
#include <stdio.h>

int main() {
      struct Node *node = generateFile("test/astTree/treeGen/main.a");
      genTree(node, "test/astTree/treeGen/astTree.dot");
}
