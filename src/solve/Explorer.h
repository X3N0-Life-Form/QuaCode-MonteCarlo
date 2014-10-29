
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
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Explorer ( );

  /**
   * Empty Destructor
   */
  virtual ~Explorer ( );


  /**
   */
  virtual void explore ( )
  {
  }

private:

  // Static Private attributes
  //  

  // Private attributes
  //  
  std::vector<Validator*> validators;
  Problem* problem;
  ResearchSpace<Variable*>* spaceTree;


};
}; // end of package namespace

#endif // EXPLORER_H
