#ifndef __NODES_H_
#define __NODES_H_

enum TypeNode { SUPERNODE, BINARYNODE, CONSTNODE };

enum TypeSuperNode { GLOBAL, BODYFOO, BODY };
enum TypeBinaryNode { DECL, DEF, IF, WHILE };
enum TypeConstNode { INT, CHAR, STRING, FLOAT };

struct Node {
      enum TypeNode typeNode;
      struct {
            enum TypeSuperNode type;
            struct Node **nodes;
      } SuperNode;

      struct {
            enum TypeBinaryNode type;
            struct Node *left;
            struct Node *right;
      } BinaryNode;

      struct {
            enum TypeConstNode type;
            union {
                  int INTEGER;
                  char CHARACTER;
                  char *STRING;
                  float FLOAT;
            } VAL;
      } ConstNode;
};

#endif
