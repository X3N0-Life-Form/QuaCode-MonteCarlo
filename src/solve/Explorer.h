
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

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   */
  virtual void explore ( )
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  
  std::vector<Validator*> validators;
  Problem* problem;
  ResearchSpace* spaceTree;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};
}; // end of package namespace

#endif // EXPLORER_H
