#include "../include/pre_fgetc.h"
#include "../include/pre_utils.h"
#include "../include/status.h"
#include "../include/tokens.h"
#include <ctype.h>
#include <libgen.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 2048
#define _POSIX1_SOURCE 2
