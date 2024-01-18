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
};

struct ReservedWords {
      const char *_INT_;
      const char *_CHAR_;
      const char *_FLOAT_;
};

extern struct Token TOKENS;
extern struct ReservedWords RESERVED_WORDS;
#endif
