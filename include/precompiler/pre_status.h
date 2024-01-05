#ifndef __ERRORS_H__
#define __ERRORS_H__

extern int nLines;
enum ERROR {
      SYNTAX_ERROR = 1,
      FILE_NO_EXISTS,
      INCLUDE_FILE_NO_EXISTS,
      DEFINE_NOT_EXISTS
};
const extern char *ERRORS[];

enum STATUS { SUCCESS, ERROR };
void reportFatalError(int nLine, enum ERROR, char *extra_info);
#endif
