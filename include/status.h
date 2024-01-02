#ifndef __ERRORS_H__
#define __ERRORS_H__

enum STATUS { SUCCESS, FILE_NOT_EXISTS, SYNTAX_ERROR };
void reportFileError(int nLine, char *file);
void reportPrecompileSyntaxError(int nLine, char *extraInfo);

#endif
