#include "../include/pre_conditional.h"
#include "../include/pre_defines.h"
#include "../include/pre_skeleton.h"
#include <stdlib.h>
#include <string.h>

int isDefined(char *token) { return existsVar(token); }
