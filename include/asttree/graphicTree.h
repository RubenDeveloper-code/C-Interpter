#ifndef __GRAPHIC_VIEW_H__
#define __GRAPHIC_VIEW_H__

#include "../../include/asttree/nodes.h"
#include <stdio.h>
void genTree(void *fatherNode, char *outFile);
void start(struct Node *node, FILE *STREAM_OUT, int layer);
char *nextNodeData(struct Node *node);

#endif
