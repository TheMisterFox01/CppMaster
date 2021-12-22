#pragma once

#include <string>
#include "scanner.h"
#include "parser.h"
#include "evaluator.h"


class calc
{

  plugin_loader plugins;

  scanner scan;

  parser parse;

  evaluator eval;
public:

  calc();


  double calculate(const std::string& expression);
};