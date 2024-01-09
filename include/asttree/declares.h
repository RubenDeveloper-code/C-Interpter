#ifndef __DECLARE_H__
#define __DECLARE_H__

#define BUFFSIZE 2048
extern void *declaresVar[];
extern void *declaresArr[];
extern void *declaresFoo[];

extern void *ptrdvar, *ptrdarr, *ptrdfoo;

void addDeclareVar(void *ptr);
void addDeclareArray(void *ptr);
void addDeclareFoo(void *ptr);
#endif
