#ifndef __NODES_H_
#define __NODES_H_

enum TypeNode { SUPERNODE, BINARYNODE, CONSTNODE };

enum TypeSuperNode { GLOBAL, BODYFOO, BODY };
enum TypeBinaryNode { DECL, DEF, IF, WHILE };
enum TypeConstNode { INT, CHAR, STRING, FLOAT };

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
      union {
            int INTEGER;
            char CHARACTER;
            char *STRING;
            float FLOAT;
      } VAL;
};

#endif
