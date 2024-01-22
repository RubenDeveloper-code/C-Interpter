#include "../../../include/asttree/readerTokens.h"
#include <stdio.h>

int main() {
      char *lineExample = "int a=10;";
      printf("firstToken: %s\n", firstTokenIn(lineExample));
      printf("endToken: %s\n", lastTokenIn(lineExample));
      printf("indexToken: %s deberia ser: =\n", tokenIn(lineExample, 2));
      printf("nextToken: %s \n", getNextToken(lineExample));
      printf("indexToken: %s deberia ser: = tambien\n",
             tokenIn(lineExample, 2));
      freeOffset();
      char *lineExample2 = "if(hola&&adios){";
      printf("pt2");
      printf("firstToken: %s\n", firstTokenIn(lineExample2));
      printf("endToken: %s\n", lastTokenIn(lineExample2));
      printf("indexToken: %s deberia ser: hola\n", tokenIn(lineExample2, 2));
      printf("nextToken: %s \n", getNextToken(lineExample2));
      printf("indexToken: %s deberia ser: hola tambien\n",
             tokenIn(lineExample2, 2));
}
