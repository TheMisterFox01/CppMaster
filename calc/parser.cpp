#include "parser.h"

// Get priority of operator
int parser::getPrior(token *op)
{
  if (op->type == token::token_type_function)
    return 6;
  else if (op->type == token::token_type_operation)
  {
    token_operation *tmp = (token_operation *)op;
    switch (tmp->symbol[0]) {
    case '(':
      return -2;
      break;
    case ')':
    case ';':
      return -1;
      break;
    case '=':
      return 0;
      break;
    case ',':
      return 1;
      break;
    case '+':
    case '-':
      return 2;
      break;
    case '*':
    case '/':
      return 3;
      break;
    case '@':
      return 4;
      break;
    case '^':
      return 5;
      break;
    }
  }
  return -1;
}

bool parser::checkAssoc(token* op1, token* op2)
{
  int p1 = getPrior(op1);
  int p2 = getPrior(op2);
  if (p1 == p2 && 
    op1->type == token::token_type_operation && 
    ((token_operation *)op1)->symbol == "^") 
    return 0;
  return p1 >= p2;
}


void parser::sendOperators(token * op, token_stack& numbers, token_stack& oper)
{
  while (!oper.empty() && checkAssoc(oper.top(), op)) {
    token *t;
    t = oper.top();
    numbers.push(t);
    oper.pop();
  }
}

parser::state_t parser::doPrefix(token* t, token_stack& numbers, token_stack& oper)
{
  if (t->type == token::token_type_number) {
    numbers.push(t);
    return STATE_SUFFIX;
  }
  else if (t->type == token::token_type_operation) {
    token_operation *tmp = (token_operation*)t;
    if (tmp->symbol == "(") {
      oper.push(t);
    }
    else if (tmp->symbol == "-") {
      tmp->symbol = '@';
      tmp->is_unary = true;
      oper.push(t);
    }
    else
      throw std::exception("Not prefix operation");
  }
  else if (t->type == token::token_type_function) {
    oper.push(t);
    return STATE_PREFIX;
  }
  else {
    throw std::exception("Wait for number or '('");
  }
  return STATE_PREFIX;
}

parser::state_t parser::doPostfix(token* t, token_stack& numbers, token_stack& oper)
{
  if (t->type == token::token_type_operation) {
    token_operation *tmp = (token_operation*)t;
    if (tmp->symbol == ")") {
      sendOperators(t, numbers, oper);
      if (oper.empty()) {
        throw std::exception("Wait for '('");
      }
      else
      {
        t = oper.top();
        oper.pop();
      }
    }
    else {
      sendOperators(t, numbers, oper);
      oper.push(t);
      return STATE_PREFIX;
    }
  }
  else 
    throw std::exception("Wait for operation or '('");
  return STATE_SUFFIX;
}

parser::state_t parser::doDone(token* t, token_stack& numbers, token_stack& oper)
{
  token_operation *tmp = new DEBUG_NEW_PLACEMENT token_operation;
  tmp->symbol = ')';
  sendOperators(tmp, numbers, oper);
  if (!oper.empty()) {
    throw std::exception("Missing ')'");
  }
  while (!numbers.empty()) {
    t = numbers.top();
    numbers.pop();
    oper.push(t);
  }
  delete tmp;
  return STATE_END;
}

token_queue& parser::parse(token_queue tokens)
{
  std::swap(rns_queue, token_queue());
  token *t;
  token_stack numbers, oper;
  state_t state = STATE_PREFIX;

  while (state != STATE_END) {
    if (state <= STATE_SUFFIX) {
      if (tokens.empty()) {        
        if (state == STATE_SUFFIX) {
          state = STATE_DONE;
        }
        else {
          throw std::exception("Unexpected end-of-expression");
        }
      }
      else
      {
        t = tokens.front();
        tokens.pop();
      }
    }

    switch (state)
    {
    case STATE_PREFIX:
      state = doPrefix(t, numbers, oper);
      break;
    case STATE_SUFFIX:
      state = doPostfix(t, numbers, oper);
      break;
    case STATE_DONE:
      state = doDone(t, numbers, oper);
      break;
    default:
      break;
    }
  }
  while (!oper.empty())
  {
    t = oper.top();
    rns_queue.push(t);
    oper.pop();
  }
  return rns_queue;
}