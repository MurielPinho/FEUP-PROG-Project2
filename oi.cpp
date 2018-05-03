// #include <string>

// #include <vector>
// #include <iostream>
// #include <fstream>
// #include <regex>
// #include "cwcreator.h"


#include <stdio.h>
#include <string.h>

int main()
{
  char  str[] = "Abdomen: belly, paunch";
  char *pch;

  printf("Splitting string \"%s\" into tokens:\n", str);
  pch = strtok(str, " ,:");

  while (pch != NULL)
  {
    printf("%s\n", pch);
    pch = strtok(NULL, " ,:");
  }
  return 0;
}
