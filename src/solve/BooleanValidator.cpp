#include "BooleanValidator.h"

using namespace solve;

// Constructors/Destructors
//  

BooleanValidator::BooleanValidator(Problem * pb):Validator(pb) {}

BooleanValidator::~BooleanValidator ( ) { }

 bool BooleanValidator::validateConstraint(Constraint * cst, std::vector<std::pair<Variable *, Value *> > values) {
 	return false;
 }



