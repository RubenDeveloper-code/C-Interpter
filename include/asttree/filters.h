#ifndef __FILTERS_H__
#define __FILTERS_H__

#define START_CONDITIONS 7
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

int _operationType(char *token);
int _typeData(char *token);
int _conditional(char *token, char *line);

enum TypeBinaryNode _typeNodeBin(char *line, char *token);
enum TypeSuperNode _typeSuperNode(char *line, char *token);
#endif
