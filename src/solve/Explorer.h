
#ifndef EXPLORER_H
#define EXPLORER_H

#include "Validator.h"
#include "../core/Problem.h"
#include "../SIBusAdapter.h"
#include "../core/Solution.h"

#include <string>
#include <vector>

using namespace core;

namespace solve {


/**
  * class Explorer
  * 
  */

class Explorer
{

private:
  std::vector<Validator*> validators;
  Problem* problem;

protected:
  SIBusAdapter* adapter;

public:

  // Constructors/Destructors
  Explorer();
  virtual ~Explorer();

  void setAdapter(SIBusAdapter* adapter);

  virtual int heuristic() = 0;

  int getArgumentValue(ConstraintArgument* arg, Solution& sol);
};
}; // end of package namespace

#endif // EXPLORER_H
