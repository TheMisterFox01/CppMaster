#pragma once
#include "def.h"

template<int N>
struct variadicVector;

template<>
struct variadicVector<1>
{
  argument head_;


  variadicVector(const argument list[], int index = 0) : head_(list[index])
  {
  }


  template<typename ClassType, typename FuncType, typename ...Args>
  int callBind(ClassType* Cl, FuncType F, Args ...args)
  {
    return std::bind(F, Cl, args..., head_.second)();
  }
};


template<int N>
struct variadicVector : variadicVector<N - 1>
{

  using base_type = variadicVector<N - 1>;

  base_type &base = static_cast<base_type &>(*this);
  

  argument head_;


  variadicVector(const argument* list, int index = 0) : variadicVector<N - 1>(list, index + 1), head_(list[index])
  {

  }

  template<typename ClassType, typename FuncType, typename ...Args>
  int callBind(ClassType* Cl, FuncType F, Args ...args)
  {
    return base.callBind(Cl, F, args..., head_.second);
  }
};