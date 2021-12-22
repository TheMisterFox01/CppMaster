#include <Windows.h>
#include <cmath>
#include "../plugin_loader.h"

binary_table my_binary_table;

extern "C" __declspec(dllexport) binary_table & RetriveBinary(void)
{
  
  my_binary_table["^"] = [](double a, double b) -> double {return std::pow(a, b); };

  return my_binary_table;
}
