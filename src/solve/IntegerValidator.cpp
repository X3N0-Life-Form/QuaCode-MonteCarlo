#include "IntegerValidator.h"

using namespace solve;

// Constructors/Destructors
//  

IntegerValidator::IntegerValidator (Problem * pb) : Validator(pb) {
}

IntegerValidator::~IntegerValidator ( ) { }

bool IntegerValidator::validateConstraint(Constraint * cst, std::vector<std::pair<Variable *, Value *> > values) {
	comparison_type CT = cst->getComparisonType();
	int value = 0;

	switch(cst->getConstraintType() ) {
		case TIMES:
			value = 1;
			for(unsigned int i = 0; i < cst->getArguments().size(); i++) {
				if (!i == cst->getArguments().size() - 1) {
					value *= Validator::getArgumentIValue(cst->getArguments()[i], values);
				}
				else {
					int lastValue = Validator::getArgumentIValue(cst->getArguments()[i], values);
					return Validator::checkComparison(value, CT, lastValue);
				}
			}
		case LINEAR:
			for(unsigned int i = 0; i < cst->getArguments().size(); i+2) {
				if (i < cst->getArguments().size() - 1) {
					value += Validator::getArgumentIValue(cst->getArguments()[i], values)* Validator::getArgumentIValue(cst->getArguments()[i+1], values);
				}
				else {
					int lastValue = Validator::getArgumentIValue(cst->getArguments()[i], values);
					return Validator::checkComparison(value, CT, lastValue);
				}
			}
		// TODO : check if we did well
		case C_EQ:
			value = Validator::getArgumentIValue(cst->getArguments()[0], values);
			for (unsigned int i = 1; i < cst->getArguments().size(); i++ ) {
				if (value != Validator::getArgumentIValue(cst->getArguments()[i], values) ) {
					return false;
				}
			}
			return true;
		default :
			cerr << "not implemented yet" << endl;
			return false;
	}
}



