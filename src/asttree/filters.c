#include "../../include/asttree/filters.h"
#include "../../include/asttree/declares.h"
#include "../../include/asttree/nodes.h"
#include "../../include/asttree/readerTokens.h"
#include "../../include/tokens.h"
#include <string.h>

int _conditional(char *token, char *line) {
      int START = START_CONDITIONS;
      const char *conditionalMTokens[] = {TOKENS.AND,      TOKENS.OR,
                                          TOKENS.EQUALITY, TOKENS.GT_OR_EQ,
                                          TOKENS.LT_OR_EQ, TOKENS.NO_EQUAL};
      const char conditionalCTokens[] = {TOKENS.GT_SIMBOL, TOKENS.LT_SIMBOL};
      char *cond = strcat(token, lendNextToken(line));
      for (int i = 0; i < 6; i++) {
            if (strcmp(cond, conditionalMTokens[i]) == 0) {
                  getNextToken(line);
                  return i + START_CONDITIONS;
            }
      }
      for (int i = 6; i < 8; i++) {
            if (token[0] == conditionalCTokens[i - 6]) {
                  return i + START_CONDITIONS;
            }
      }
      return NONE;
}

// name;
int _operationType(char *token) {
      if (token[0] == TOKENS.ADD)
            return ADD;
      if (token[0] == TOKENS.RES)
            return RES;
      if (token[0] == TOKENS.MULT)
            return MULT;
      if (token[0] == TOKENS.DIV)
            return DIV;
      return NONE;
}

// int a = c+b
enum TypeBinaryNode _typeNodeBin(char *line, char *token) {
      enum TypeBinaryNode nodetype = NONE;
      if (_typeData(token) != NONE) {
            if (existsVar(lendNextToken(line)) == NONE)
                  nodetype = DECL;
            else /**error**/
                  ;
      } else if (lendNextToken(line)[0] == TOKENS.EQUAL) {
            nodetype = DEF;
      } else if (strcmp(token, RESERVED_WORDS._WHILE_) == 0) {
            nodetype = LOOP;
      }
      return nodetype;
}

enum TypeSuperNode _typeSuperNode(char *line, char *token) {
      enum TypeSuperNode tsn = NONE;
      if (strcmp(token, RESERVED_WORDS._IF_) == 0) {
            tsn = IF;
      } else if (strcmp(token, RESERVED_WORDS._FOR_) == 0) {
            tsn = FOR;
      }

      return tsn;
}

int _typeData(char *token) {
      if (strcmp(token, RESERVED_WORDS._INT_) == 0)
            return INT;
      if (strcmp(token, RESERVED_WORDS._CHAR_) == 0)
            return CHAR;
      if (strcmp(token, RESERVED_WORDS._FLOAT_) == 0)
            return FLOAT;
      return NONE;
}
