#ifndef __PRE_DEFINES_H__
#define __PRE_DEFINES_H__

#include <stdio.h>

#define MAXBUFFVARS 2048
#define VALID 1
#define INVALID -1

enum TYPE { NORMAL, MACRO };

struct Define {
      char *name;
      char *value;
      enum TYPE type;
      char **ARGS;
      int valid;
};
extern struct Define *DEFINES[MAXBUFFVARS];
extern int variableIndex;

char *getDefineVariable(FILE *stream);
char *getDefineValue(FILE *stream);
int addVariableAndValue(char *VARIABLE, char *VALUE);
int existsVar(const char *VARIABLE);
int undefVar(const char *VARIABLE);
void clearDefines();

int resolveDefines(char *line);
void getMacroName(char *nameMacro, char *src);
void getMacroArgs(char *argsMacro, char *src);
void getMacroArgsCall(char *argsCallMacro, char *pos);
void getArrayMacroArgs(char **dest, char *src);
int prepareMacro(char *dest, char **prototipeARGS, char **callARGS);

#endif
