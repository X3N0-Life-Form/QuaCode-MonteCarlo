
#ifndef PROBLEM_H
#define PROBLEM_H

#include "Variable.h"
#include "Constraint.h"
#include "Domain.h"
#include "Value.h"

#include <string>
#include <vector>


namespace core {


/**
  * class Problem
  * 
  */
class Problem
{
private:
  std::vector<Variable*> variables;
  std::vector<Constraint*> constraints;

public:

  // Constructors/Destructors
  Problem ( );
  virtual ~Problem ( );

  void addVariable(Variable* var);
  void addConstraint(Constraint* cst);

  std::vector<Variable *> getVariables();
  std::vector<Constraint *> getConstraints();

  /**
   * @return NULL if the variable could not be found.
   */
  Variable* getVariable(std::string varName);
  Domain* getDomain(int lowerBoundary, int upperBoundary); 
};
}; // end of package namespace

#endif // PROBLEM_H
