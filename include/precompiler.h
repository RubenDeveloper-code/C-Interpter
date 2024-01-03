#ifndef __PRECOMPILER_H__
#define __PRECOMPILER_H__

#include <stdio.h>
int precompileAll(char **files, int nfiles, char *out_path);
int precompileFile(char *file, char *out_path);
char *prepareOutFileName(char *in_file, char *out_path);
int precompile(FILE *stream, char *file_src_path);
int findPrecompilerOrder(FILE *stream, char *file_src_path);
int filterPrecompileOrder(FILE *stream, FILE *stream_out, char *file_src_path);

char *getIncludeFile(FILE *stream);
int includeFile(char *file, FILE *stream_out, char *file_src_path);

char *getDefineVariable(FILE *stream);
char *getDefineValue(FILE *stream);
int addVariableAndValue(char *VARIABLE, char *VALUE);
int resolveDefines(char *line);
void getMacroName(char *src, char *nameMacro);
void getMacroArgs(char *src, char *argsMacro);
void getMacroArgsCall(char *pos, char *argsCallMacro);
void getArrayMacroArgs(char **dest, char *src);
int prepareMacro(char *dest, char **prototipeARGS, char **callARGS);

int ffgetc(FILE *stream);
void skipComments(FILE *stream, char *token, char *prevToken);
void manageSpaces(FILE *stream, char *token, char *prevToken);

void funputc(FILE *stream);
void testVariables();
#endif
