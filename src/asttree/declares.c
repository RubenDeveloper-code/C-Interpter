#include "../../include/asttree/declares.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ConstNode declaresVar[BUFFSIZE];
struct ConstNode declaresArr[BUFFSIZE];
struct ConstNode declaresFoo[BUFFSIZE];

struct ConstNode *ptrdvar = declaresVar;
struct ConstNode *ptrdarr = declaresArr;
struct ConstNode *ptrdfoo = declaresFoo;

int contVars = 0;
void addDeclareVar(struct ConstNode *ptr) {
      *ptrdvar++ = *ptr;
      contVars++;
}
void addDeclareArray(struct ConstNode *ptr) {
      ptrdarr = ptr;
      ptrdarr++;
}
void addDeclareFoo(struct ConstNode *ptr) {
      ptrdfoo = ptr;
      ptrdfoo++;
}

int existsVar(char *name) {
      struct ConstNode *local_ptr = declaresVar;
      int index = 0;
      for (int i = 0; i < contVars; i++) {
            if (strcmp(local_ptr[i].value, name) == 0)
                  return i;
      }
      return -1;
}
