#include "../../include/asttree/graphicTree.h"
#include "../../include/asttree/generator.h"
#include "../../include/asttree/nodes.h"
#include <stdio.h>

void genTree(void *fatherNode, char *outFile) {
      if (fatherNode != NULL) {
            FILE *out = fopen(outFile, "w");
            fprintf(out, "digraph Arbol{\n");
            start(fatherNode, out);
      } else {
            printf("NODO PADRE VACIO");
      }
}
void start(struct Node *node, FILE *STREAM_OUT) {
      if (node->typeNode == SUPERNODE) {
            for (int i = 0; node->SuperNode.nodes != NULL;
                 i++, node->SuperNode.nodes++) {
                  fprintf(STREAM_OUT, "%i -> %i", node->SuperNode.type,
                          node->SuperNode.nodes[i]->typeNode);
                  start(*node->SuperNode.nodes, STREAM_OUT);
            }
      } else if (node->typeNode == BINARYNODE) {
            if (node->BinaryNode.left != NULL) {
                  struct Node *leftnode = node->BinaryNode.left;
                  if (leftnode == NULL)
                        return;
                  if (leftnode->typeNode == CONSTNODE) {
                        fprintf(STREAM_OUT, "%i -> %i", node->BinaryNode.type,
                                leftnode->ConstNode.VAL.INTEGER);
                  } else
                        fprintf(STREAM_OUT, "%i -> %i", node->BinaryNode.type,
                                node->BinaryNode.left->BinaryNode.type);
                  start(node->BinaryNode.left, STREAM_OUT);
                  struct Node *rightnode = node->BinaryNode.right;
                  if (leftnode == NULL)
                        return;
                  if (rightnode->typeNode == CONSTNODE) {
                        fprintf(STREAM_OUT, "%i -> %i", node->BinaryNode.type,
                                rightnode->ConstNode.VAL.INTEGER);
                  } else
                        fprintf(STREAM_OUT, "%i -> %i", node->BinaryNode.type,
                                node->BinaryNode.right->BinaryNode.type);
            }
            if (node->BinaryNode.right != NULL)
                  start(node->BinaryNode.right, STREAM_OUT);
      };
}
