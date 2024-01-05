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
      const char PRECOMPILE_ORDER;
      const char *INCLUDE_ORDER;
      const char INCLUDE_FIELD_OPEN;
      const char INCLUDE_FIELD_CLOSED;
      const char *DEFINE;
      const char *IFDEF;
      const char *IFNDEF;
      const char *ENDIF;
      const char *ELSE;
      const char *UNDEF;
};
extern struct Token TOKENS;
#endif
