#include "../include/precompiler.h"
#include <stddef.h>
#include <stdint.h>
#define _POSIX1_SOURCE 2
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 2048

// TODO: define(Sustituir), ifdef, ifndef, endif

int nLines;
FILE *stream_out;

enum TYPE { NORMAL, MACRO };
struct Define {
      char *name;
      char *value;
      enum TYPE type;
      char **ARGS;
} *DEFINES[BUFFSIZE];

int variableIndex = 0;

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
} TOKENS = {' ', '"',  ',',      '/',     '(',      ')',
            '*', '\n', '\0',     '_',     '#',      "include",
            '<', '>',  "define", "ifdef", "ifndef", "endif"};

// cambiar a enum
struct Status {
      const int SUCCESS;
      const int FILE_NOT_EXISTS;
      const int SYNTAX_ERROR;
} STATUS = {0, 1, 2};

int precompileAll(char *files[], int nfiles) {
      char **ptr = files;
      while (nfiles-- > 0) {
            printf("archivo a precopilar: %i\n", nfiles + 1);
            int status = precompileFile(*ptr++);
            if (status != STATUS.SUCCESS)
                  return status;
      }
      return STATUS.SUCCESS;
}

// Precompila el .c incluyendo todo...a
int precompileFile(char *file) {
      FILE *stream = fopen(file, "r");
      char *fileoutext = ".pre";
      char *filename =
          malloc((strlen(file) + strlen(fileoutext) + 1) * sizeof(char));
      strcpy(filename, file);
      strcat(filename, fileoutext);
      stream_out = fopen(filename, "a+");
      if (stream == NULL)
            return STATUS.FILE_NOT_EXISTS;
      int status = precompile(stream);

      fclose(stream_out);
      free(filename);
      return status;
}
// sirve para precompilar .h o .c
int precompile(FILE *stream) {
      char token;
      int status;
      int Analyze = 1;
      char BUFF[BUFFSIZE];
      char *ptr = BUFF;
      while ((token = ffgetc(stream)) != EOF) {
            if (token == TOKENS.QUOTES)
                  Analyze = !Analyze;
            if (Analyze) {
                  if (token == TOKENS.PRECOMPILE_ORDER) {
                        status = filterPrecompileOrder(stream, stream_out);
                        if (status != STATUS.SUCCESS)
                              return status;
                        continue;
                  }
            }
            if (token == TOKENS.END_LINE || token == TOKENS.ZERO_END) {
                  *ptr++ = TOKENS.END_LINE;
                  *ptr = TOKENS.ZERO_END;
                  resolveDefines(BUFF);
                  fputs(BUFF, stream_out);
                  ptr = BUFF;
            } else {
                  *ptr++ = token;
            }
      }
      return STATUS.SUCCESS;
}

int resolveDefines(char *line) {
      for (int i = 0; i < variableIndex; i++) {
            char *pos;
            char *temp = malloc(sizeof(char) * BUFFSIZE);
            if (DEFINES[i]->type == NORMAL) {
                  while ((pos = strstr(line, DEFINES[i]->name)) != NULL) {
                        snprintf(temp, BUFFSIZE, "%.*s%s%s%c",
                                 (int)(pos - line), line, DEFINES[i]->value,
                                 pos + strlen(DEFINES[i]->name),
                                 TOKENS.ZERO_END);
                        strcpy(line, temp);
                  }
            } else if (DEFINES[i]->type == MACRO) {
                  // checar todo desde aca ese error sale porque sale
                  char nameMacro[BUFFSIZE];
                  getMacroName(DEFINES[i]->name, nameMacro);
                  while ((pos = strstr(line, nameMacro)) != NULL) {
                        char argsCallMacro[BUFFSIZE];
                        getMacroArgsCall(pos, argsCallMacro);
                        printf("MacroArgsCall %s\n", argsCallMacro);
                        char *callARGS[BUFFSIZE];
                        getMacroID(callARGS, argsCallMacro);
                        char *solvedMacro = malloc(sizeof(char) * BUFFSIZE);
                        strcpy(solvedMacro, DEFINES[i]->value);
                        int check = prepareMacro(solvedMacro, DEFINES[i]->ARGS,
                                                 callARGS);
                        if (check != STATUS.SUCCESS)
                              return check;
                        char buffLine[BUFFSIZE];
                        snprintf(buffLine, BUFFSIZE, "%.*s%s%s",
                                 (int)(pos - line), line, solvedMacro,
                                 pos + strlen(nameMacro) +
                                     strlen(argsCallMacro));
                        strcpy(line, buffLine);
                        pos += strlen(solvedMacro);
                  }
            }
      }
      return STATUS.SUCCESS;
}
void getMacroName(char *src, char *nameMacro) {
      snprintf(nameMacro, BUFFSIZE, "%.*s%c",
               (int)(strchr(src, TOKENS.OPEN_PARENTHESIS) - src), src,
               TOKENS.ZERO_END);
}
void getMacroArgs(char *src, char *argsMacro) {
      snprintf(argsMacro, BUFFSIZE, "%s%c",
               (strchr(src, TOKENS.OPEN_PARENTHESIS)), TOKENS.ZERO_END);
}
void getMacroArgsCall(char *pos, char *argsCallMacro) {
      char *open = strchr(pos, TOKENS.OPEN_PARENTHESIS);
      char *close = strchr(pos, TOKENS.CLOSED_PARENTHESIS);
      strncpy(argsCallMacro, open, close - open + 1);
      argsCallMacro[close - open + 1] = TOKENS.ZERO_END;
}

void getMacroID(char **dest, char *src) {
      char **ptr_dest = malloc(sizeof(char *) * BUFFSIZE);
      ptr_dest = dest;
      char *ptr_src = src;
      char *ptr = *ptr_dest = malloc(sizeof(char) * BUFFSIZE);
      while (*ptr_src != TOKENS.CLOSED_PARENTHESIS) {
            if (*ptr_src == TOKENS.COMA) {
                  *ptr = TOKENS.ZERO_END;
                  printf("getMacroID->args: %s from: %s\n", *ptr_dest, src);
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
      printf("getMacroID->args: %s from: %s\n", *ptr_dest, src);
}

int prepareMacro(char *dest, char **prototipeARGS, char **callARGS) {
      char *ptr = dest;
      char **ptr_pptargs = malloc(sizeof(char *) * BUFFSIZE);
      ptr_pptargs = prototipeARGS;
      char **ptr_callargs = malloc(sizeof(char *) * BUFFSIZE);
      ptr_callargs = callARGS;
      char buff[BUFFSIZE];
      printf("prototipe: %s call: %s\n", prototipeARGS[0], callARGS[0]);
      int offset = 0;
      while (*ptr_pptargs != NULL) {
            ptr = dest + offset;
            if (*ptr_callargs == NULL) {
                  return STATUS.SYNTAX_ERROR;
            }
            while ((ptr = strstr(ptr, *ptr_pptargs)) != NULL) {
                  snprintf(buff, BUFFSIZE, "%.*s%s%s", (int)(ptr - dest), dest,
                           *ptr_callargs, ptr + strlen(*ptr_pptargs));
                  offset += strlen(*ptr_pptargs);
                  ptr += offset;
                  strcpy(dest, buff);
            }
            free(*ptr_callargs);
            ptr_pptargs++;
            ptr_callargs++;
      }
      if (*ptr_callargs != NULL)
            return STATUS.SYNTAX_ERROR;
      return STATUS.SUCCESS;
}

// include<...> || define ....
int filterPrecompileOrder(FILE *stream, FILE *stream_out) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while (isalnum(*ptr = ffgetc(stream)))
            ptr++;
      *ptr = TOKENS.ZERO_END;
      if (strcmp(token, TOKENS.INCLUDE_ORDER) == 0) {
            free(token);
            char *file = getIncludeFile(stream);
            return includeFile(file, stream_out);
      }
      if (strcmp(token, TOKENS.DEFINE) == 0) {
            free(token);
            char *name = getDefineVariable(stream);
            char *value = getDefineValue(stream);
            return addVariableAndValue(name, value);
      }
      return STATUS.SYNTAX_ERROR;
}

// variable
char *getDefineVariable(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      char LIMIT_TOKEN = TOKENS.SPACE;
      while ((*ptr = fgetc(stream)) != LIMIT_TOKEN && *ptr != TOKENS.QUOTES) {
            if (*ptr == TOKENS.OPEN_PARENTHESIS)
                  LIMIT_TOKEN = TOKENS.CLOSED_PARENTHESIS;
            ptr++;
      }
      if (*ptr == TOKENS.QUOTES)
            ungetc(*ptr, stream);
      if (*ptr == TOKENS.CLOSED_PARENTHESIS)
            ptr++;
      *ptr = TOKENS.ZERO_END;
      printf("Variable: %s\n", token);
      return token;
}

char *getDefineValue(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while ((*ptr = fgetc(stream)) != TOKENS.END_LINE)
            ptr++;
      *ptr = TOKENS.ZERO_END;
      return token;
}

int addVariableAndValue(char *VARIABLE, char *VALUE) {
      struct Define *tempVar = malloc(sizeof(struct Define));
      if (strchr(VARIABLE, TOKENS.OPEN_PARENTHESIS)) {
            if (strchr(VARIABLE, TOKENS.CLOSED_PARENTHESIS) == NULL) {
                  printf("error parentesis: %s\n", VARIABLE);
                  return STATUS.SYNTAX_ERROR;
            }
            tempVar->type = MACRO;
            char *args = malloc(sizeof(char) * BUFFSIZE);
            getMacroArgs(VARIABLE, args);
            char *buff[BUFFSIZE];
            getMacroID(buff, args);
            char **ptrSyntaxcheck = buff;
            // comprobacion si los argumentos son iguales
            tempVar->ARGS = buff;
      } else {
            tempVar->type = NORMAL;
      }
      tempVar->name = strdup(VARIABLE);
      tempVar->value = strdup(VALUE);
      DEFINES[variableIndex++] = tempVar;
      return STATUS.SUCCESS;
}

// namefile>
char *getIncludeFile(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while ((*ptr = ffgetc(stream)) != TOKENS.INCLUDE_FIELD_CLOSED)
            ptr++;
      if (*ptr != TOKENS.INCLUDE_FIELD_CLOSED) {
            // syntax error errorReport(error, line)
      }
      *ptr = TOKENS.ZERO_END;
      return token;
}

// namefile.h
int includeFile(char *file, FILE *stream_out) {
      FILE *include_stream = fopen(file, "r");
      precompile(include_stream);
      free(file);
      return STATUS.SUCCESS;
}

char ffgetc(FILE *stream) {
      static char prevToken;
      char token = fgetc(stream);
      skipComments(stream, &token, &prevToken);
      manageSpaces(stream, &token, &prevToken);
      if (token == TOKENS.END_LINE) {
            nLines++;
      }
      prevToken = token;
      return token;
}

// simple y multilinea...
void skipComments(FILE *stream, char *token, char *prevToken) {
      if (*token == TOKENS.SLASH && *prevToken == TOKENS.SLASH) {
            while ((*token = fgetc(stream)) != TOKENS.END_LINE)
                  ;
            funputc(stream_out);
            *token = fgetc(stream);
      } else if (*prevToken == TOKENS.SLASH && *token == TOKENS.ASTERISK) {
            *prevToken = *token;
            while ((*token = fgetc(stream)) != EOF) {
                  if (*token == TOKENS.SLASH && *prevToken == TOKENS.ASTERISK)
                        break;
                  *prevToken = *token;
            }
            *token = fgetc(stream);
            funputc(stream_out);
      }
}

void manageSpaces(FILE *stream, char *token, char *prevToken) {
      if (*token == TOKENS.SPACE) {
            while ((*token = fgetc(stream)) == TOKENS.SPACE)
                  ;
            if (((isalnum(*token) || *token == TOKENS.UNDERSCORE) &&
                 (isalnum(*prevToken) || *prevToken == TOKENS.UNDERSCORE))) {
                  ungetc(*token, stream);
                  *token = TOKENS.SPACE;
            }
      }
}
void funputc(FILE *stream) {
      fseek(stream, -1, SEEK_END);
      ftruncate(fileno(stream), ftell(stream));
}

void testVariables() {
      for (int i = 0; i < variableIndex; i++) {
            printf("\nvar: |%s| value: |%s|", DEFINES[i]->name,
                   DEFINES[i]->value);
      }
}
