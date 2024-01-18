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

void addDeclareVar(struct ConstNode *ptr) { *ptrdvar++ = *ptr; }
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
      while (local_ptr != NULL) {
            if (strcmp(local_ptr->value, name) == 0)
                  return index;
            index++;
            local_ptr++;
      }
      return -1;
}
