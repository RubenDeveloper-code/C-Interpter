#include "../include/pre_defines.h"
#include "../include/pre_skeleton.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int variableIndex = 0;
struct Define *DEFINES[MAXBUFFVARS];
int resolveDefines(char *line) {
      enum STATUS status = SUCCESS;
      char *ptr_line = line;
      for (int i = 0; i < variableIndex && status == SUCCESS; i++) {
            char *pos;
            char *temp = malloc(sizeof(char) * BUFFSIZE);
            if (DEFINES[i]->valid == INVALID)
                  continue;
            if (DEFINES[i]->type == NORMAL) {
                  while (
                      (pos = strstr(ptr_line, DEFINES[i]->name)) != NULL &&
                      !isBetweenQuotes(pos, strlen(DEFINES[i]->name), line)) {
                        int index_preValue = (pos - line);
                        char *postValue = (pos + strlen(DEFINES[i]->name));
                        snprintf(temp, BUFFSIZE, "%.*s%s%s%c", index_preValue,
                                 line, DEFINES[i]->value, postValue,
                                 TOKENS.ZERO_END);
                        ptr_line += strlen(DEFINES[i]->value);
                        strcpy(line, temp);
                  }
            } else if (DEFINES[i]->type == MACRO) {
                  while (
                      (pos = strstr(ptr_line, DEFINES[i]->name)) != NULL &&
                      status == SUCCESS &&
                      !isBetweenQuotes(pos, strlen(DEFINES[i]->name), line)) {
                        char argsCallMacro[BUFFSIZE];
                        char **callARGS = malloc(sizeof(char *) * BUFFSIZE);
                        char *macro = malloc(sizeof(char) * BUFFSIZE);

                        getMacroArgsCall(argsCallMacro, pos);
                        getArrayMacroArgs(callARGS, argsCallMacro);
                        strcpy(macro, DEFINES[i]->value);
                        status =
                            prepareMacro(macro, DEFINES[i]->ARGS, callARGS);

                        char buffLine[BUFFSIZE];
                        int index_preMacro = pos - line;
                        char *postMacro = pos + strlen(DEFINES[i]->name) +
                                          strlen(argsCallMacro);

                        snprintf(buffLine, BUFFSIZE, "%.*s%s%s", index_preMacro,
                                 line, macro, postMacro);
                        strcpy(line, buffLine);
                        ptr_line += strlen(macro);
                  }
            }
      }
      return status;
}
void getMacroName(char *nameMacro, char *src) {
      snprintf(nameMacro, BUFFSIZE, "%.*s%c",
               (int)(strchr(src, TOKENS.OPEN_PARENTHESIS) - src), src,
               TOKENS.ZERO_END);
}
void getMacroArgs(char *argsMacro, char *src) {
      snprintf(argsMacro, BUFFSIZE, "%s%c",
               (strchr(src, TOKENS.OPEN_PARENTHESIS)), TOKENS.ZERO_END);
}
void getMacroArgsCall(char *argsCallMacro, char *pos) {
      char *open = strchr(pos, TOKENS.OPEN_PARENTHESIS);
      char *close = strchr(pos, TOKENS.CLOSED_PARENTHESIS);
      strncpy(argsCallMacro, open, close - open + 1);
      argsCallMacro[close - open + 1] = TOKENS.ZERO_END;
}

void getArrayMacroArgs(char **dest, char *src) {
      char **ptr_dest = malloc(sizeof(char *) * BUFFSIZE);
      ptr_dest = dest;
      char *ptr_src = src;
      char *ptr = *ptr_dest = malloc(sizeof(char) * BUFFSIZE);
      while (*ptr_src != TOKENS.CLOSED_PARENTHESIS) {
            if (*ptr_src == TOKENS.COMA) {
                  *ptr = TOKENS.ZERO_END;
                  ptr_dest++;
                  *ptr_dest = malloc(sizeof(char) * BUFFSIZE);
                  ptr = *ptr_dest;
            }
            if ((isalnum(*ptr_src) || *ptr_src == TOKENS.UNDERSCORE)) {
                  *ptr++ = *ptr_src++;
            } else {
                  ptr_src++;
            }
      }
      *ptr = TOKENS.ZERO_END;
}

int prepareMacro(char *dest, char **prototipeARGS, char **callARGS) {
      enum STATUS status = SUCCESS;
      char *ptr = dest;
      char **ptr_pptargs = malloc(sizeof(char *) * BUFFSIZE);
      ptr_pptargs = prototipeARGS;
      char **ptr_callargs = malloc(sizeof(char *) * BUFFSIZE);
      ptr_callargs = callARGS;
      char buff[BUFFSIZE];
      int offset = 0;
      while (*ptr_pptargs != NULL) {
            ptr = dest + offset;
            while ((ptr = strstr(ptr, *ptr_pptargs)) != NULL) {
                  int indexPreArg = ptr - dest;
                  char *postArg = ptr + strlen(*ptr_pptargs);
                  snprintf(buff, BUFFSIZE, "%.*s%s%s", indexPreArg, dest,
                           *ptr_callargs, postArg);
                  offset += strlen(*ptr_callargs);
                  ptr += offset;
                  strcpy(dest, buff);
            }
            free(*ptr_callargs);
            ptr_pptargs++;
            ptr_callargs++;
      }
      if (*ptr_callargs != NULL && *callARGS != NULL) {
            status = SYNTAX_ERROR;
      }
      return status;
}

// variable
char *getDefineVariable(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      char LIMIT_TOKEN = TOKENS.SPACE;
      while ((*ptr = fgetc(stream)) != LIMIT_TOKEN && *ptr != TOKENS.QUOTES &&
             *ptr != TOKENS.END_LINE) {
            if (*ptr == TOKENS.OPEN_PARENTHESIS)
                  LIMIT_TOKEN = TOKENS.CLOSED_PARENTHESIS;
            ptr++;
      }
      if (*ptr == TOKENS.QUOTES || *ptr == TOKENS.END_LINE)
            ungetc(*ptr, stream);
      if (*ptr == TOKENS.CLOSED_PARENTHESIS)
            ptr++;
      *ptr = TOKENS.ZERO_END;
      return token;
}

char *getDefineValue(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      int (*getter)(FILE *stream);
      int test;
      if ((test = fgetc(stream)) == TOKENS.QUOTES) {
            getter = fgetc;
      } else {
            getter = ffgetc;
      }
      ungetc(test, stream);
      while ((*ptr = getter(stream)) != TOKENS.END_LINE)
            ptr++;
      *ptr = TOKENS.ZERO_END;
      return token;
}

int addVariableAndValue(char *VARIABLE, char *VALUE) {
      struct Define *tempVar = malloc(sizeof(struct Define));
      if (strchr(VARIABLE, TOKENS.OPEN_PARENTHESIS)) {
            if (strchr(VARIABLE, TOKENS.CLOSED_PARENTHESIS) == NULL) {
                  reportPrecompileSyntaxError(nLines, "parentesis no cerrado");
            }
            char *args = malloc(sizeof(char) * BUFFSIZE);
            char **arrayArgs = malloc(sizeof(char *));
            char *nameMacro = malloc(sizeof(char) * BUFFSIZE);
            getMacroArgs(args, VARIABLE);
            getArrayMacroArgs(arrayArgs, args);
            getMacroName(nameMacro, VARIABLE);

            tempVar->type = MACRO;
            tempVar->name = nameMacro;
            tempVar->ARGS = arrayArgs;
      } else {
            tempVar->name = strdup(VARIABLE);
            tempVar->type = NORMAL;
      }
      if (VALUE[0] == TOKENS.ZERO_END) {
            if (tempVar->type == NORMAL) {
                  tempVar->value = " ";
            } else {
                  reportPrecompileSyntaxError(
                      nLines, "Macro con argumentos debe hacer algo");
            }
      } else {
            tempVar->value = strdup(VALUE);
      }
      tempVar->valid = VALID;
      DEFINES[variableIndex++] = tempVar;
      return SUCCESS;
}

int undefVar(const char *VARIABLE) {
      int undefined = 0;
      if (existsVar(VARIABLE)) {
            for (int i = 0; i < variableIndex && !undefined; i++) {
                  if (strcmp(VARIABLE, DEFINES[i]->name) == 0) {
                        DEFINES[i]->valid = INVALID;
                        undefined = 1;
                  }
            }
      }
      return undefined;
}

int existsVar(const char *VARIABLE) {
      int exists = 0;
      for (int i = 0; i < variableIndex && !exists; i++) {
            printf("consulta: |%s| defines: |%s|", VARIABLE, DEFINES[i]->name);
            if (strcmp(VARIABLE, DEFINES[i]->name) == 0)
                  exists = 1;
      }
      return exists;
}

void clearDefines() {
      for (int i = 0; i < variableIndex; i++) {
            DEFINES[i] = NULL;
      }
      variableIndex = 0;
}
