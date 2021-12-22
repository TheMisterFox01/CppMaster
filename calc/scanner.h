#pragma once
#include <string>
#include <memory>

#include "token.h"
class scanner
{
  private:
    std::string my_expression;
    int expression_index;
    token_queue my_queue; 

    void scanNumber(void);
    void scanOperation(void);
    void scanFunction(void);
  public:


  token_queue& scan(const std::string& expression);

 
  void cleanQueue(void);


  ~scanner();
};