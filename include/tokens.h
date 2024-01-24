#ifndef __TOKENS_H__
#define __TOKENS_H__
struct Token {
      const char SPACE;
      const char QUOTES;
      const char COMA;
      const char SLASH;
      const char OPEN_PARENTHESIS;
      const char CLOSED_PARENTHESIS;
      const char ASTERISK;
      const char JUMP_LINE;
      const char ZERO_END;
      const char UNDERSCORE;
      const char END_LINE;
      const char BRACKET_OPEN;
      const char BRACKET_CLOSED;
      const char EQUAL;
      const char ADD;
      const char RES;
      const char MULT;
      const char DIV;
      const char OPEN_KEY;
      const char CLOSED_KEY;
      const char LT_SIMBOL;
      const char GT_SIMBOL;
      const char *AND;
      const char *OR;
      const char NEGATION;
      const char *EQUALITY;
      const char *GT_OR_EQ;
      const char *LT_OR_EQ;
      const char *NO_EQUAL;
};

struct ReservedWords {
      const char *_INT_;
      const char *_CHAR_;
      const char *_FLOAT_;
      const char *_IF_;
      const char *_ELSE_;
      const char *_WHILE_;
      const char *_FOR_;
};

extern struct Token TOKENS;
extern struct ReservedWords RESERVED_WORDS;
#endif
