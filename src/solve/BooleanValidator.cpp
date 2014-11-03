#include "BooleanValidator.h"

#include <iostream>

using namespace solve;
using namespace std;

// Constructors/Destructors
//  

BooleanValidator::BooleanValidator(Problem * pb):Validator(pb) {}

BooleanValidator::~BooleanValidator ( ) { }

 bool BooleanValidator::validateConstraint(Constraint * cst, std::vector<std::pair<Variable *, Value *> > values) {
 	bool value = true;
 	comparison_type CT = cst->getComparisonType();

 	switch(cst->getConstraintType() ) {
 		case AND :
 			for(unsigned int i = 0; i < cst->getArguments().size(); i++) {
				if (!i == cst->getArguments().size() - 1) {
					value = Validator::getArgumentBValue(cst->getArguments()[i], values) && value;
				}
				else {
					bool lastValue = Validator::getArgumentBValue(cst->getArguments()[i], values);
					return Validator::checkComparison(value, CT, lastValue);
				}
			}


 		case OR : 		
 			value = value && Validator::getArgumentBValue(cst->getArguments()[0], values);
 			for(unsigned int i = 1; i < cst->getArguments().size(); i++) {
				if (!i == cst->getArguments().size() - 1) {
					value = Validator::getArgumentBValue(cst->getArguments()[i], values) || value;
				}
				else {
					bool lastValue = Validator::getArgumentBValue(cst->getArguments()[i], values);
					return Validator::checkComparison(value, CT, lastValue);
				}
			}


 		case XOR : 		
 			value = value && Validator::getArgumentBValue(cst->getArguments()[0], values);
 			for(unsigned int i = 1; i < cst->getArguments().size(); i++) {
				if (!i == cst->getArguments().size() - 1) {
					value = Validator::getArgumentBValue(cst->getArguments()[i], values) != value;
				}
				else {					
					bool lastValue = Validator::getArgumentBValue(cst->getArguments()[i], values);
					return Validator::checkComparison(value, CT, lastValue);
				}
			}

 		case IMP : 	
 			value = value && Validator::getArgumentBValue(cst->getArguments()[0], values);	
 			for(unsigned int i = 1; i < cst->getArguments().size(); i++) {
				if (!i == cst->getArguments().size() - 1) {
					if (!value) {
						value = true;
					}
					else if (Validator::getArgumentBValue(cst->getArguments()[i], values) == true) {
						value = true;
					}
					else {
						value = false;
					}
				}
				else {
					bool lastValue = Validator::getArgumentBValue(cst->getArguments()[i], values);
					return Validator::checkComparison(value, CT, lastValue);
				}
			}

 		default : 		
			cerr << "not implemented yet" << endl;
			return false;

 	}
 }



