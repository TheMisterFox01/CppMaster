#include "scanner.h"

void scanner::cleanQueue(void)
{
  while (!my_queue.empty())
  {
    delete my_queue.front();
    my_queue.pop();
  }
}

void scanner::scanNumber(void)
{
  token_number *T = new DEBUG_NEW_PLACEMENT token_number;
  std::string::size_type new_index;
  T->value = std::stod(my_expression.substr(expression_index), &new_index);
  my_queue.push(T);
  expression_index += new_index;
}

void scanner::scanOperation(void)
{
  token_operation * T = new DEBUG_NEW_PLACEMENT token_operation;
  T->symbol = my_expression[expression_index++];
  my_queue.push(T);
}

void scanner::scanFunction(void)
{
  char buf[300] = { 0 };
  int i = 0;
  do
  {
    if (i < 300 - 1)
      buf[i++] = my_expression[expression_index];
    expression_index++;
  } while (isalpha(my_expression[expression_index]));

  token_function* T = new DEBUG_NEW_PLACEMENT token_function;
  T->name = buf;
  my_queue.push(T);
}

token_queue &scanner::scan(const std::string &expression)
{
  if (my_queue.size() != 0)
    cleanQueue();

  my_expression = expression;
  expression_index = 0;
  while (expression_index < my_expression.size())
  {
    /* Remove spaces */
    if (isspace(my_expression[expression_index]))
    {
      expression_index++;
      continue;
    }
    switch (my_expression[expression_index])
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '.':
        scanNumber();
        break;
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '(':
      case ')':
        scanOperation();
        break;
      default:
      {
       
        if (isalpha(my_expression[expression_index])) 
        {
          scanFunction();
          break;
        }
        
        {
          cleanQueue();
          throw std::exception("Unknown symbol in Scanner");
        }
        break;
      }
    }
  }
  return my_queue;
}

scanner::~scanner()
{
  cleanQueue();
}