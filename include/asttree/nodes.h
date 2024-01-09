#ifndef __NODES_H_
#define __NODES_H_

enum NODES {
      NONE = -1,
      TYPE,
      DECLVAR,
      DECLARRAY,
      DECLFOO,
      ASSGN,
      IF,
      FOR,
      WHILE
};

struct Node {
      void *left;
      void *right;
};

struct SimpleInt {
      int data;
};

struct Assign {
      char *var;
      void *val;
};

enum TYPES_DATA { INT, CHAR, FLOAT, VOID };
enum TYPE { SIMPLE, ARRAY, FOO };
struct Declare {
      enum TYPES_DATA typedata;
      enum TYPE type;
      char *name;
};

struct Define {
      void *varDefined;
      void *value;
};

enum BINOP { ADD, RES, MULT, DIV };
struct BinOp {
      enum BINOP type;
      void *v1;
      void *v2;
      int data;
};

#endif
