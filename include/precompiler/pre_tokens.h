#ifndef __PRE_TOKENS_H__
#define __PRE_TOKENS_H__

struct TokensPecompiler {
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
extern struct TokensPecompiler TOKENS_PRECOMPILER;

#endif
