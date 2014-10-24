#include "IntegerConstraint.h"

using namespace core;

// Constructors/Destructors
//  

IntegerConstraint::IntegerConstraint ( constraint_type cstT, comparison_type cmpT): Constraint(cstT, cmpT) {
}

IntegerConstraint::~IntegerConstraint ( ) { }

//  
// Methods
//  


// Accessor methods
//  

Type IntegerConstraint::getType() {
  return INTEGER;
}

// Other methods
//  


