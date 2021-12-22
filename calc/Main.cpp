#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <iostream>
#include <sstream>
#include "calc.h"

int mainLoop(void)
{
  calc calc;
  std::string string;
  double rez = 0;
  while (true)
  {
    int i = 0;
    int len;
    std::getline(std::cin, string);
    if (string.size() == 0) {
      break;
    }

    len = string.length();

    for (i = 0; i < len; i++) {
      if (isspace(string[i]) == 0) {
        break;
      }
    }

    if (i == string.length()) {
      printf("%s\n", string.c_str());
      continue;
    }
    if (i < len && string[i] == '/' && string[i + 1] == '/') { 
      printf("%s\n", string.c_str());
      continue;
    }
    printf("%s == ", string.c_str());

    try
    {
      rez = calc.calculate(string);
      printf("%g\n", rez);
    }
    catch (std::exception& ex)
    {
      printf("ERROR : %s\n", ex.what());
    }
  }
  return 0;
}

#include <stdlib.h>
int main(int argc, char* argv[]) {
  int res = mainLoop();
  _CrtDumpMemoryLeaks();
  return res;
}