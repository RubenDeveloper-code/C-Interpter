#include "../include/precompiler.h"
#include "../include/pre_conditional.h"
#include "../include/pre_defines.h"
#include "../include/pre_includes.h"
#include "../include/pre_skeleton.h"

// Separando ando
//   TODO: ifdef, ifndef, endif
FILE *stream_out;

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
int filterPrecompileOrder(FILE *stream, FILE *stream_out, char *file_src_path) {
      enum STATUS status = SUCCESS;
      char *token = malloc(BUFFSIZE * sizeof(char));
      char *ptr = token;
      while (isalnum(*ptr = ffgetc(stream)))
            ptr++;
      *ptr = TOKENS.ZERO_END;
      if (strcmp(token, TOKENS.INCLUDE_ORDER) == 0) {
            char *file = getIncludeFile(stream);
            status = includeFile(file, stream_out, file_src_path);
      } else if (strcmp(token, TOKENS.DEFINE) == 0) {
            char *name = getDefineVariable(stream);
            char *value = getDefineValue(stream);
            status = addVariableAndValue(name, value);
      } else if (strcmp(token, TOKENS.IFDEF) == 0) {
      }
      free(token);
      return status;
}
