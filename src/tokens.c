#include "../include/tokens.h"
struct Token TOKENS = {' ', '"', ',',  '/',  '(', ')',  '*',  '\n', '\0', '_',
                       ';', '[', ']',  '=',  '+', '-',  '*',  '/',  '{',  '}',
                       '<', '>', "&&", "||", '!', "==", ">=", "<=", "!="};
struct ReservedWords RESERVED_WORDS = {"int",  "char",  "float", "if",
                                       "else", "while", "for"};
