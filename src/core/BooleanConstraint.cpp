#include "BooleanConstraint.h"

using namespace core;

// Constructors/Destructors
//  

BooleanConstraint::BooleanConstraint (constraint_type cstT, comparison_type cmpT ): Constraint(cstT, cmpT) {
}

BooleanConstraint::~BooleanConstraint ( ) { }

//  
// Methods
//  



// Accessor methods
//  
Type BooleanConstraint::getType() {
  return BOOLEAN;
}

// Other methods
//  


