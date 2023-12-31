#ifndef __PRECOMPILER_H__
#define __PRECOMPILER_H__

#include <stdio.h>
int precompileAll(char **files, int nfiles);
int precompileFile(char *file);
int precompile(FILE *stream);
int findPrecompilerOrder(FILE *stream);
int filterPrecompileOrder(FILE *stream, FILE *stream_out);

char *getIncludeFile(FILE *stream);
int includeFile(char *file, FILE *stream_out);

char *getDefineVariable(FILE *stream);
char *getDefineValue(FILE *stream);
int addVariableAndValue(char *VARIABLE, char *VALUE);
int resolveDefines(char *line);
void getMacroName(char *src, char *nameMacro);
void getMacroArgs(char *src, char *argsMacro);
void getMacroArgsCall(char *pos, char *argsCallMacro);
void getMacroID(char **dest, char *src);
int prepareMacro(char *dest, char **prototipeARGS, char **callARGS);

char ffgetc(FILE *stream);
void skipComments(FILE *stream, char *token, char *prevToken);
void manageSpaces(FILE *stream, char *token, char *prevToken);

void funputc(FILE *stream);
void testVariables();
#endif
