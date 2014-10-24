
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
public:

  // Constructors/Destructors
  //  
  Problem ( );
  virtual ~Problem ( );

private:
  std::vector<Variable*> variables;
  std::vector<Constraint*> constraints;

  std::vector<std::pair<Variable *, Value *> > values;

public:


  void addVariable(Variable* var);
  void addConstraint(Constraint* cst);
  void addValue(Variable* var, Value* val);

  std::vector<Variable *> getVariables();
  std::vector<Constraint *> getConstraints();
  std::vector<std::pair<Variable *, Value *> > getValues();

  /**
   * @return NULL if the variable could not be found.
   */
  Variable* getVariable(std::string varName);
  Domain* getDomain(int lowerBoundary, int upperBoundary);

  void generateValueVector();



};
}; // end of package namespace

#endif // PROBLEM_H
