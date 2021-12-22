#pragma once
#include <map>
#include "token.h"


class parser
{
  private:
    
    token_queue rns_queue;

    
    enum state_t {
      STATE_PREFIX, STATE_SUFFIX, STATE_DONE, STATE_END
    };

    
    state_t doPrefix(token* t, token_stack& numbers, token_stack& oper);

   
    state_t doPostfix(token* t, token_stack& numbers, token_stack& oper);

   
    state_t doDone(token* t, token_stack& numbers, token_stack& oper);

    
    void sendOperators(token* op, token_stack& numbers, token_stack& oper);

    
    bool checkAssoc(token *op1, token *op2);

    
    int getPrior(token* op);

  public:
   
    token_queue& parse(token_queue tokens);
};