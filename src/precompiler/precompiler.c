#include "../../include/precompiler/precompiler.h"
#include "../../include/precompiler/pre_conditional.h"
#include "../../include/precompiler/pre_defines.h"
#include "../../include/precompiler/pre_includes.h"
#include "../../include/precompiler/pre_skeleton.h"
#include <string.h>

// Separando ando
//   TODO: ifdef, ifndef, endif
FILE *stream_out;
int wrte = 1;
int openIfs = -1;
int ifwrt[2048];

int precompileAll(char *files[], int nfiles, char *out_path) {
      // limpiar variables, reiniciar conteo de lineas
      char **ptr = files;
      while (nfiles-- > 0) {
            nLines = 0;
            clearDefines();
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
      } else {
            reportFatalError(nLines, FILE_NO_EXISTS, file);
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
            if (analyze && token == TOKENS_PRECOMPILER.PRECOMPILE_ORDER) {
                  status = filterPrecompileOrder(stream, stream_out, path_src);
            } else if ((token == TOKENS.END_LINE || token == TOKENS.ZERO_END)) {
                  *ptr++ = TOKENS.END_LINE;
                  *ptr = TOKENS.ZERO_END;
                  status = resolveDefines(BUFF);
                  fputs(BUFF, stream_out);
                  ptr = BUFF;
            } else if (wrte) {
                  *ptr++ = token;
            }
      }
      return status;
}

// include<...> || define ....
int filterPrecompileOrder(FILE *stream, FILE *stream_out, char *file_src_path) {
      enum STATUS status = SUCCESS;
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while (isalnum(*ptr = ffgetc(stream)))
            ptr++;
      *ptr = TOKENS.ZERO_END;
      if (wrte && strcmp(token, TOKENS_PRECOMPILER.INCLUDE_ORDER) == 0) {
            char *file = getIncludeFile(stream);
            status = includeFile(file, stream_out, file_src_path);
      } else if (wrte && strcmp(token, TOKENS_PRECOMPILER.DEFINE) == 0) {
            char *name = getDefineVariable(stream);
            char *value = getDefineValue(stream);
            status = addVariableAndValue(name, value);
      } else if (strcmp(token, TOKENS_PRECOMPILER.IFDEF) == 0) {
            if (wrte)
                  wrte = isDefined(ffgetcUntil(stream, TOKENS.END_LINE));
            ifwrt[++openIfs] = wrte;
      } else if (strcmp(token, TOKENS_PRECOMPILER.IFNDEF) == 0) {
            if (wrte)
                  wrte = !isDefined(ffgetcUntil(stream, TOKENS.END_LINE));
            ifwrt[++openIfs] = wrte;
      } else if (strcmp(token, TOKENS_PRECOMPILER.ELSE) == 0) {
            if (openIfs > 0) { // hay otro nivel
                  wrte = ifwrt[openIfs] = ifwrt[openIfs - 1] && !wrte;
            } else if (openIfs == 0) {
                  wrte = !wrte;
                  ifwrt[openIfs] = wrte;
            } else {
                  reportFatalError(nLines, SYNTAX_ERROR,
                                   "ELSE without any oppened IFXXX");
            }
      } else if (strcmp(token, TOKENS_PRECOMPILER.ENDIF) == 0) {
            if (openIfs > 0) { // hay otro nivel
                  wrte = ifwrt[openIfs - 1];
            } else if (openIfs == 0) {
                  wrte = 1;
            } else {
                  reportFatalError(nLines, SYNTAX_ERROR,
                                   "ENDIF without any oppened IFXXX");
            }
            openIfs--;
      } else if (strcmp(token, TOKENS_PRECOMPILER.UNDEF) == 0) {
            char *namevar = ffgetcUntil(stream, TOKENS.END_LINE);
            if (undefVar(namevar)) {
                  status = SUCCESS;
            } else {
                  reportFatalError(nLines, DEFINE_NOT_EXISTS, namevar);
            }
      }
      free(token);
      return status;
}
