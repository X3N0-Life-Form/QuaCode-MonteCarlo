
#ifndef EXPLORER_H
#define EXPLORER_H

#include "Validator.h"
#include "../core/Problem.h"
#include "../core/ResearchSpace.h"

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

public:

  // Constructors/Destructors
  Explorer();
  virtual ~Explorer();


  /**
   */
  virtual void explore ( )
  {
  }


};
}; // end of package namespace

#endif // EXPLORER_H
