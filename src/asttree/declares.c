#include "../../include/asttree/declares.h"

void *declaresVar[BUFFSIZE];
void *declaresArr[BUFFSIZE];
void *declaresFoo[BUFFSIZE];

void *ptrdvar = declaresVar;
void *ptrdarr = declaresArr;
void *ptrdfoo = declaresFoo;

void addDeclareVar(void *ptr) { ptrdvar = ptr; }
void addDeclareArray(void *ptr) { ptrdarr = ptr; }
void addDeclareFoo(void *ptr) { ptrdfoo = ptr; }
