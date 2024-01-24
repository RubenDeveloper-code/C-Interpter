#ifndef __NODES_H_
#define __NODES_H_

enum TypeNode { SUPERNODE, BINARYNODE, CONSTNODE };

enum TypeSuperNode { GLOBAL, BODYFOO, BODY, SECONDBODY, IF, FOR };
enum TypeBinaryNode {
      DECL,
      DEF,
      LOOP,
      ADD,
      RES,
      MULT,
      DIV,
      AND,
      OR,
      EQ,
      GEQ,
      LEQ,
      NEQ,
      GT,
      LT,

};
enum TypeConstNode { INT, CHAR, STRING, FLOAT, VAR, TYPEDATA };

struct Node {
      enum TypeNode type;
      void *node;
};

struct SuperNode {
      enum TypeSuperNode type;
      struct Node **nodes;
      int contNodes;
};

struct BinaryNode {
      enum TypeBinaryNode type;
      struct Node *left;
      struct Node *right;
};

struct ConstNode {
      enum TypeConstNode type;
      char *value;
};

#endif
