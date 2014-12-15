#include "Problem.h"

using namespace core;

// Constructors/Destructors
//  

Problem::Problem ( ) {
}

Problem::~Problem ( ) { }

 

void Problem::addVariable(Variable* var) {
  variables.push_back(var);
}

void Problem::addConstraint(Constraint* cst) {
  constraints.push_back(cst);
}


std::vector<Variable *> Problem::getVariables() {
  return variables;
}

std::vector<Constraint *> Problem::getConstraints() {
  return constraints;
}
  

Variable* Problem::getVariable(std::string varName) {
  for (Variable* var : variables) {
    if (var->getName() == varName) {
      return var;
    }
  }
  return NULL;
}

Domain* Problem::getDomain(int lowerBoundary, int upperBoundary) {
  // it would be cool if we had a domain vector ...
  for (Variable* var : variables) {
    Domain* dom = var->getDomain();
    if (dom->getFirstValue() == lowerBoundary
	&& dom->getLastValue() == upperBoundary) {
      return dom;
    }
  }
  return NULL;
}





// Other methods
//  


