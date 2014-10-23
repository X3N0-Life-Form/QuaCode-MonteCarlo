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


  void Problem::addValue(Variable* var, Value* val) {
  	for (std::pair<Variable*, Value*> currentPair : values) {
  		if (var->getName() == currentPair.first->getName()) {
  			currentPair.second = val;
  			break;
  		}
  	}
  }

  std::vector<Variable *> Problem::getVariables() {
  		return variables;
  }
  std::vector<Constraint *> Problem::getConstraints() {
  		return constraints;
  }
  std::vector<std::pair<Variable *, Value *> > Problem::getValues(){
  	return values;
  }

  void Problem::generateValueVector(){
  	for (unsigned int i = 0; i < variables.size(); i++) {
  		values.push_back(std::pair<Variable*, Value*>(variables[i], NULL));
  	}
  }



// Other methods
//  


