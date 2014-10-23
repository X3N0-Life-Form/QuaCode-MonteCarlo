
#ifndef PROBLEM_H
#define PROBLEM_H

#include "Variable.h"
#include "Constraint.h"
#include "Domain.h"

#include <string>
#include <vector>



namespace core {


/**
  * class Problem
  * 
  */

class Problem
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Problem ( );

  /**
   * Empty Destructor
   */
  virtual ~Problem ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


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
  std::vector<Variable*> variables;
  std::vector<Constraint*> constraints;
  std::vector<Domain*> domains;
public:


  // Private attribute accessor methods
  //  

  void addVariable(Variable* var);

private:

public:


  // Private attribute accessor methods
  //  

private:



};
}; // end of package namespace

#endif // PROBLEM_H
