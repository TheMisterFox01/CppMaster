#pragma once
#include <string>
#include <queue>
#include <stack>

struct token
{

  enum
  {
    token_type_number,    
    token_type_operation, 
    token_type_function   
  } type; 

  virtual ~token() = default;
};

struct token_number : public token
{
  double value; 

  token_number()
  {
    type = token_type_number;
  }

  virtual ~token_number() = default;
};

struct token_operation : public token
{
  std::string symbol;    
  bool is_unary = false; 

  token_operation()
  {
    type = token_type_operation;
  }

  virtual ~token_operation() = default;
};


struct token_function : public token
{
  std::string name; 

  token_function()
  {
    type = token_type_function;
  }

  virtual ~token_function() = default;
};


using token_queue = std::queue<token *>;

using token_stack = std::stack<token *>;

#ifdef _DEBUG
#define DEBUG_NEW_PLACEMENT (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW_PLACEMENT
#endif
