#include "../include/precompiler.h"
#include "../include/status.h"
#include <stddef.h>
#include <stdint.h>
#define _POSIX1_SOURCE 2
#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 2048

// TODO DEJAR BIEN CHULO ESTE CODIGO AJUAAAA
//  TODO: ifdef, ifndef, endif

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
int precompileAll(char *files[], int nfiles, char *out_path) {
      char **ptr = files;
      while (nfiles-- > 0) {
            printf("archivo a precopilar: %i\n", nfiles + 1);
            int status = precompileFile(*ptr++, out_path);
            if (status != SUCCESS)
                  return status;
      }
      return SUCCESS;
}

// Precompila el .c incluyendo todo...a
int precompileFile(char *file, char *out_path) {
      FILE *stream = fopen(file, "r");
      enum STATUS status = SUCCESS;
      if (stream != NULL) {
            char *out = prepareOutFileName(file, out_path);
            stream_out = fopen(out, "a+");
            char *cpy_file = strdup(file);
            char *dir = strdup(dirname(cpy_file));
            char end_path[] = {TOKENS.SLASH, TOKENS.ZERO_END};
            strcat(dir, end_path);
            status = precompile(stream, dir);
      }
      fclose(stream);
      return status;
}

char *prepareOutFileName(char *in_file, char *out_path) {
      char *filename_out = malloc((BUFFSIZE) * sizeof(char));
      char *fileoutext = ".pre";
      *filename_out = TOKENS.ZERO_END;
      strcat(filename_out, out_path);
      char *ptr_slash = strrchr(in_file, TOKENS.SLASH);

      if (ptr_slash != NULL)
            strcat(filename_out, ((strrchr(in_file, TOKENS.SLASH)) + 1));
      else
            strcat(filename_out, in_file);
      strcat(filename_out, fileoutext);
      return filename_out;
}
// sirve para precompilar .h o .c
int precompile(FILE *stream, char *path_src) {
      enum STATUS status = SUCCESS;
      char BUFF[BUFFSIZE];
      char *ptr = BUFF;
      int analyze = 1;
      char token;
      while ((token = ffgetc(stream)) != EOF && status == SUCCESS) {
            analyze = ((token == TOKENS.QUOTES) ? !analyze : analyze);
            if (analyze && token == TOKENS.PRECOMPILE_ORDER) {
                  status = filterPrecompileOrder(stream, stream_out, path_src);
            } else if (token == TOKENS.END_LINE || token == TOKENS.ZERO_END) {
                  *ptr++ = TOKENS.END_LINE;
                  *ptr = TOKENS.ZERO_END;
                  status = resolveDefines(BUFF);
                  fputs(BUFF, stream_out);
                  ptr = BUFF;
            } else {
                  *ptr++ = token;
            }
      }
      return status;
}
// include<...> || define ....
//
int filterPrecompileOrder(FILE *stream, FILE *stream_out, char *file_src_path) {
      enum STATUS status = SUCCESS;
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while (isalnum(*ptr = ffgetc(stream)))
            ptr++;
      *ptr = TOKENS.ZERO_END;
      if (strcmp(token, TOKENS.INCLUDE_ORDER) == 0) {
            char *file = getIncludeFile(stream);
            free(token);
            status = includeFile(file, stream_out, file_src_path);
      } else if (strcmp(token, TOKENS.DEFINE) == 0) {
            free(token);
            char *name = getDefineVariable(stream);
            char *value = getDefineValue(stream);
            status = addVariableAndValue(name, value);
      }
      return status;
}
// namefile>
char *getIncludeFile(FILE *stream) {
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while ((*ptr = ffgetc(stream)) != TOKENS.INCLUDE_FIELD_CLOSED &&
             *ptr != TOKENS.QUOTES)
            ptr++;
      if (*ptr != TOKENS.INCLUDE_FIELD_CLOSED && *ptr != TOKENS.QUOTES) {
            reportPrecompileSyntaxError(nLines, token);
      }
      *ptr = TOKENS.ZERO_END;
      return token;
}

// namefile.h || el archivo se obtiene de donde este el .c relativo a este...
int includeFile(char *file, FILE *stream_out, char *path_src) {
      enum STATUS status = SUCCESS;
      char *filepath = malloc(sizeof(char) * BUFFSIZE);
      strcpy(filepath, path_src);
      strcat(filepath, file);
      FILE *include_stream = fopen(filepath, "r");
      status = precompile(include_stream, path_src);
      free(file);
      free(filepath);
      fclose(include_stream);
      return status;
}

int resolveDefines(char *line) {
      // WARNING: "ARGS" sutituye cuando no deberia entre comillas
      enum STATUS status = SUCCESS;
      char *ptr_line = line;
      for (int i = 0; i < variableIndex && status == SUCCESS; i++) {
            char *pos;
            char *temp = malloc(sizeof(char) * BUFFSIZE);
            if (DEFINES[i]->type == NORMAL) {
                  while ((pos = strstr(ptr_line, DEFINES[i]->name)) != NULL) {
                        int index_preValue = (pos - line);
                        char *postValue = (pos + strlen(DEFINES[i]->name));
                        snprintf(temp, BUFFSIZE, "%.*s%s%s%c", index_preValue,
                                 line, DEFINES[i]->value, postValue,
                                 TOKENS.ZERO_END);
                        ptr_line += strlen(DEFINES[i]->value);
                        strcpy(line, temp);
                  }
            } else if (DEFINES[i]->type == MACRO) {
                  char nameMacro[BUFFSIZE];
                  getMacroName(DEFINES[i]->name, nameMacro);
                  while ((pos = strstr(ptr_line, nameMacro)) != NULL &&
                         status == SUCCESS) {
                        char argsCallMacro[BUFFSIZE];
                        getMacroArgsCall(pos, argsCallMacro);

                        char **callARGS = malloc(sizeof(char *) * BUFFSIZE);
                        getArrayMacroArgs(callARGS, argsCallMacro);

                        char *macro = malloc(sizeof(char) * BUFFSIZE);
                        strcpy(macro, DEFINES[i]->value);

                        status =
                            prepareMacro(macro, DEFINES[i]->ARGS, callARGS);

                        char buffLine[BUFFSIZE];
                        int index_preMacro = pos - line;
                        char *postMacro =
                            pos + strlen(nameMacro) + strlen(argsCallMacro);
                        snprintf(buffLine, BUFFSIZE, "%.*s%s%s", index_preMacro,
                                 line, macro, postMacro);
                        strcpy(line, buffLine);
                        ptr_line += strlen(macro);
                  }
            }
      }
      return status;
}
// voltear para que src quede como segundo argumento
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
      if (*ptr_callargs != NULL) {
            return SYNTAX_ERROR;
      }
      return SUCCESS;
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
      printf("Variable: %s\n", token);
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
                  printf("error parentesis: %s\n", VARIABLE);
                  return SYNTAX_ERROR;
            }
            tempVar->type = MACRO;
            char *args = malloc(sizeof(char) * BUFFSIZE);
            getMacroArgs(VARIABLE, args);
            char **buff = malloc(sizeof(char *));
            getArrayMacroArgs(buff, args);
            char **ptrSyntaxcheck = buff;
            // comprobacion si los argumentos son iguales
            tempVar->ARGS = buff;
            printf("args prototipe 0:%s\n", tempVar->ARGS[0]);
      } else {
            tempVar->type = NORMAL;
      }
      if (VALUE[0] == TOKENS.ZERO_END) {
            if (tempVar->type == NORMAL) {
                  tempVar->value = " ";
            } else {
                  return SYNTAX_ERROR;
            }
      } else {
            tempVar->value = strdup(VALUE);
      }
      tempVar->name = strdup(VARIABLE);
      DEFINES[variableIndex++] = tempVar;
      return SUCCESS;
}

int ffgetc(FILE *stream) {
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
