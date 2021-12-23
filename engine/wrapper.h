#pragma once
#include "def.h"
#include "variadicVector.h"


class Wrapper_base
{
public:

  virtual int execute(const argument(&args)[], int NumberOfElements) = 0;
};
ee Engine, Wrapper, Wrapper_base
*/
template <typename ClassType, typename FuncType, int N>
class Wrapper_templated : public Wrapper_base
{
private:

  std::vector<argument> Arguments;

  std::unordered_map<std::string, argument*> FindMap;

  ClassType* Class;

  FuncType Func;

public:
  Wrapper_templated(void) = delete;


  Wrapper_templated(ClassType* Cl, FuncType F, const argument(&args)[N])
  {

    Func = F;
    Class = Cl;

    for (int i = 0; i < N; i++)
      Arguments.push_back(args[i]);

    for (int i = 0; i < N; i++)
      FindMap[args[i].first] = &Arguments[i];
  }

  virtual int execute(const argument(&args)[], int NumberOfElements)
  {
    if (NumberOfElements != N)
      throw std::exception("Invalid amount of arguments");

    for (int i = 0; i < NumberOfElements; i++)
      if (FindMap.find(args[i].first) == FindMap.end())
        throw std::exception(("Unknown argument " + args[i].first).c_str());

    for (int i = 0; i < NumberOfElements; i++)
      FindMap[args[i].first]->second = args[i].second;

    variadicVector<N> V(&(Arguments[0]));

    return V.callBind(Class, Func);
  }
};

class Wrapper
{
private:

  Wrapper_base *wrapper;
public:

  template <typename ClassType, typename FuncType, int N>
  Wrapper(ClassType* Cl, FuncType F, const argument(&args)[N])
  {
    wrapper = new Wrapper_templated<ClassType, FuncType, N>(Cl, F, args);
  }

  int execute(const argument(&args)[], int NumberOfElements)
  {
    return wrapper->execute(args, NumberOfElements);
  }

  ~Wrapper()
  {
	delete this->wrapper;
  }
};
