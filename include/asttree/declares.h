#ifndef __DECLARE_H__
#define __DECLARE_H__

#include "nodes.h"
#define BUFFSIZE 2048
extern struct ConstNode declaresVar[];
extern struct ConstNode declaresArr[];
extern struct ConstNode declaresFoo[];

extern struct ConstNode *ptrdvar, *ptrdarr, *ptrdfoo;

void addDeclareVar(struct ConstNode *ptr);
int existsVar(char *name);
void addDeclareArray(struct ConstNode *ptr);
void addDeclareFoo(struct ConstNode *ptr);
#endif
