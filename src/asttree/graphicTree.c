#include "../../include/asttree/graphicTree.h"
#include "../../include/asttree/generator.h"
#include "../../include/asttree/nodes.h"
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *BINARYNODESTOSTRING[] = {"DECL", "DEF", "IF", "WHILE"};
char *SUPERNODETOSTRING[] = {"GLOBAL", "BODYFOO", "BODY"};
char *CONSTNODETOSTRING[] = {"INT", "CHAR", "STRING", "FLOAT"};

int genRandomId() {
      unsigned char buff[4];
      RAND_bytes(buff, sizeof(buff));
      unsigned int res;
      memcpy(&res, buff, sizeof(res));
      return res;
}

void genTree(void *fatherNode, char *outFile) {
      if (fatherNode != NULL) {
            FILE *out = fopen(outFile, "w");
            fprintf(out, "digraph Arbol{\n");
            start(fatherNode, out, genRandomId());
            fprintf(out, "\n}");
      } else {
            printf("NODO PADRE VACIO");
      }
}

// forma2 pipipipi
void start(struct Node *node, FILE *STREAM_OUT, int id) {
      if (node == NULL)
            return;
      if (node->type == SUPERNODE) {
            struct SuperNode *superNode = node->node;
            for (int i = 0; i < superNode->contNodes; i++) {
                  unsigned int randomIDchild = genRandomId();
                  fprintf(STREAM_OUT, "%s%u -> %s%u\n",
                          SUPERNODETOSTRING[superNode->type], id,
                          nextNodeData(superNode->nodes[i]), randomIDchild);
                  start(superNode->nodes[i], STREAM_OUT, randomIDchild);
            }
      } else if (node->type == BINARYNODE) {
            unsigned int randomIDchild = genRandomId();
            struct BinaryNode *binaryNode = node->node;
            fprintf(STREAM_OUT, "%s%u -> %s%u\n",
                    BINARYNODESTOSTRING[binaryNode->type], id,
                    nextNodeData(binaryNode->left), randomIDchild);
            start(binaryNode->left, STREAM_OUT, randomIDchild);
            fprintf(STREAM_OUT, "%s%u -> %s%u\n",
                    BINARYNODESTOSTRING[binaryNode->type], id,
                    nextNodeData(binaryNode->right), randomIDchild);
            start(binaryNode->right, STREAM_OUT, randomIDchild);
      }
}

char *nextNodeData(struct Node *node) {
      char *res = malloc(sizeof(char) * 100);
      if (node->type == SUPERNODE) {
            struct SuperNode *sp = node->node;
            res = strdup(SUPERNODETOSTRING[sp->type]);
      }
      if (node->type == BINARYNODE) {
            struct BinaryNode *bn = node->node;
            res = strdup(BINARYNODESTOSTRING[bn->type]);
      }
      if (node->type == CONSTNODE) {
            struct SuperNode *cn = node->node;
            res = strdup(CONSTNODETOSTRING[cn->type]);
      }
      return res;
}
