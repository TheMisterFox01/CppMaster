#include "Calc.h"
#include <string.h>
#include <ctype.h>

calc::calc(void) : eval()
{
  // save them
  binary_table operations = plugins.dll_binary_table;
  unary_table functions = plugins.dll_unary_table;

  // edit data
  operations["+"] = [](double a, double b) -> double {return a + b; };
  operations["-"] = [](double a, double b) -> double {return a - b; };
  operations["*"] = [](double a, double b) -> double {return a * b; };
  operations["/"] = [](double a, double b) -> double {return a / b; };

  // unary minus
  functions["@"] = [](double a) -> double {return -a; };

  // set operations
  eval.set_op(operations, functions);
}

double calc::calculate(const std::string &expression)
{
    token_queue &scanned_queue = scan.scan(expression);
    token_queue &RPN_queue = parse.parse(scanned_queue);
    return eval.eval(RPN_queue);
}
