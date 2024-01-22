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

int _nodeType(char *token) {
      // if (isTypeData(token) != NONE || token == RESERVED_WORDS._IF_)
      return BINARYNODE;
      // return NONE;
}
// int a = c+b
enum TypeBinaryNode _typeNodeBin(char *line) {
      enum TypeBinaryNode nodetype = NONE;
      if (_typeData(firstTokenIn(line)) != NONE) {
            if (existsVar(tokenIn(line, 1)) == NONE) {
                  nodetype = DECL;
            } else if (tokenIn(line, 2)[0] == TOKENS.EQUAL) {
                  nodetype = DEF;
            }
      } else if (strcmp(firstTokenIn(line), RESERVED_WORDS._IF_) == 0)
            nodetype = IF;

      return nodetype;
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
