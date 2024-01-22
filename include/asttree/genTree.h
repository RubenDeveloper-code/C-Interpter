#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "../../include/asttree/nodes.h"
#include <stdio.h>

void *generateFile(char *file);
void addtoGlobalNode(void *Node);
char *getLine(FILE *STREAM);

#endif
