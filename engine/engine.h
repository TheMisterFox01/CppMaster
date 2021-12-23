#pragma once
#include "def.h"
#include "wrapper.h"



class Engine
{
private:

  std::unordered_map<std::string, Wrapper*> Commands;
public:


  void register_command(Wrapper* wrap, std::string name)
  {
    Commands[name] = wrap;
  }


  template<int N>
  int execute(std::string command, const argument(&Args)[N])
  {
    return Commands[command]->execute((const argument (&)[])Args, N);
  }
};