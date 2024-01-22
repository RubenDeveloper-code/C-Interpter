#ifndef __FILTERS_H__
#define __FILTERS_H__

#define START_CONDITIONS 8
#define NONE -1

enum Conditions {
      _AND_ = START_CONDITIONS,
      _OR_,
      _EQ_,
      _GEQ_,
      _LEQ_,
      _NEQ_,
      _GT_,
      _LT_
};
enum Typedata { _INT_, _CHAR_, _STRING_, _FLOAT_ };

int _nodeType(char *token);
int _operationType(char *token);
int _typeData(char *token);
int _conditional(char *token, char *line);

enum TypeNode _typeNode(char *token);
enum TypeBinaryNode _typeNodeBin(char *line);
#endif
