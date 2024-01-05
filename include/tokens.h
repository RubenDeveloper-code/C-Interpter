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
      const char END_LINE;
      const char ZERO_END;
      const char UNDERSCORE;
};
extern struct Token TOKENS;
#endif
