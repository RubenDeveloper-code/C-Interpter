#include "../../../include/asttree/readerTokens.h"
#include <stdio.h>

int main() {
      char *lineExample = "int a=10;";
      printf("firstToken: %s\n", lendFirstToken(lineExample));
      printf("endToken: %s\n", lendLastToken(lineExample));
      printf("indexToken: %s deberia ser: =\n", lendToken(lineExample, 2));
      printf("nextToken: %s \n", getNextToken(lineExample));
      printf("indexToken: %s deberia ser: 1\n", lendToken(lineExample, 2));
      freeOffset();
      char *lineExample2 = "if(hola&&adios){";
      printf("pt2");
      printf("firstToken: %s\n", lendFirstToken(lineExample2));
      printf("endToken: %s\n", lendLastToken(lineExample2));
      printf("indexToken: %s deberia ser: hola\n", lendToken(lineExample2, 2));
      printf("nextToken: %s \n", getNextToken(lineExample2));
      printf("indexToken: %s deberia ser: &\n", lendToken(lineExample2, 2));
}
