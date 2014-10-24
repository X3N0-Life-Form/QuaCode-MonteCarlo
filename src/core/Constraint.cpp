#include "Constraint.h"


using namespace core;

// Constructors/Destructors
//  

Constraint::Constraint (constraint_type cstT, comparison_type cmpT ) {
	constraintType = cstT;
	comparisonType = cmpT;
}

Constraint::~Constraint ( ) { }


// Accessor methods
// 

  constraint_type Constraint::getConstraintType () {
  	return constraintType;
  }
  comparison_type Constraint::getComparisonType() {
  	return comparisonType;
  }
  std::vector<ConstraintArgument *> Constraint::getArguments() {
  	return arguments;
  }

  // adds variable into var

  void Constraint::addArgument(ConstraintArgument * var) {
  	arguments.push_back(var);
  }


// Other methods
//  


