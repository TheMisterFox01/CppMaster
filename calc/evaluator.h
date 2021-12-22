#pragma once
#include <map>
#include "token.h"
#include "plugin_loader.h"


class evaluator
{
private:
 
  binary_table operations;
  
  unary_table functions;


  token_stack evaluation_stack;

  void processNumber(token_number *t);

  void processOperation(token_operation *t);

  void processFunction(token_function *t);

  void processUnary(std::string &symbol);

  void processBinary(std::string &symbol);

public:

  void set_op(binary_table& op, unary_table& func)
  {
      operations = op;
      functions = func;
  }


  double eval(token_queue rpn_tokens);
};