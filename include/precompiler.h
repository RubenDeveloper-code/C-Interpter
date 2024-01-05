#ifndef __PRECOMPILER_H__
#define __PRECOMPILER_H__

#include <stdio.h>

extern FILE *stream_out;
extern int wrte;
extern int openIfs;
extern int ifwrt[];

int precompileAll(char **files, int nfiles, char *out_path);
int precompileFile(char *file, char *out_path);
char *prepareOutFileName(char *in_file, char *out_path);
int precompile(FILE *stream, char *file_src_path);
int findPrecompilerOrder(FILE *stream, char *file_src_path);
int filterPrecompileOrder(FILE *stream, FILE *stream_out, char *file_src_path);

#endif
