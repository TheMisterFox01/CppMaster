#include "evaluator.h"

void evaluator::processUnary(std::string &symbol)
{
  token *a;

  if (functions.find(symbol) == functions.end())
  {
    throw std::exception("No such unary operation");
  }

  a = evaluation_stack.top();
  evaluation_stack.pop();
  if (a->type != token::token_type_number)
    throw std::exception("invlaid operand");
  token_number* a_num = (token_number*)a;
  a_num->value = functions[symbol](a_num->value);
  evaluation_stack.push(a);
}

void evaluator::processBinary(std::string &symbol)
{
  token *a, *b;

  if (operations.find(symbol) == operations.end())
  {
    throw std::exception("No such binary operation");
  }

  a = evaluation_stack.top();
  evaluation_stack.pop();
  b = evaluation_stack.top();
  evaluation_stack.pop();
  if (a->type != token::token_type_number ||
    b->type != token::token_type_number)
    throw std::exception("invlaid operands");
  token_number* a_num = (token_number*)a;
  token_number* b_num = (token_number*)b;

  a_num->value = operations[symbol](b_num->value, a_num->value);

  evaluation_stack.push(a);
}

void evaluator::processNumber(token_number *t)
{
  evaluation_stack.push(t);
}

void evaluator::processOperation(token_operation *op)
{
  if (op->is_unary)
  {
    processUnary(op->symbol);
  }
  else
  {
    processBinary(op->symbol);
  }
}

void evaluator::processFunction(token_function *func)
{
  processUnary(func->name);
}

double evaluator::eval(token_queue rpn_queue)
{
  token *t;
  
  std::swap(evaluation_stack, token_stack());

  // process queue
  while (!rpn_queue.empty())
  {
    t = rpn_queue.front();
    rpn_queue.pop();
    if (t->type == token::token_type_number)
    {
      processNumber((token_number *)t);
    }
    else if (t->type == token::token_type_function)
    {
      processFunction((token_function*)t);
    }
    else if (t->type == token::token_type_operation)
    {
      processOperation((token_operation *)t);
    }
  }
  t = evaluation_stack.top();
  if (evaluation_stack.size() > 1 ||
    t->type != token::token_type_number)
  {
    throw std::exception("Incorrect expression");
  }
  return ((token_number*)t)->value;
}