#ifndef __PRE_INCLUDES_H__
#define __PRE_INCLUDES_H__

#include <stdio.h>

char *getIncludeFile(FILE *stream);
int includeFile(char *file, FILE *stream_out, char *file_src_path);

#endif
