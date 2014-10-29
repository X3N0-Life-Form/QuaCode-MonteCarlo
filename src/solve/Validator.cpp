#include "Validator.h"

using namespace solve;

// Constructors/Destructors
//  

Validator::Validator (Problem * pb) :prob(pb) {
}

Validator::~Validator ( ) { }

//  
// Methods
//  
int Validator::getArgumentIValue(ConstraintArgument* argument, std::vector<std::pair<Variable *, Value *> > values) {
	Variable* var = dynamic_cast<Variable*>(argument);
	if (var != NULL) {
		return getVariableValue(var, values)->getiValue();
	} else {
		Constant* constant = dynamic_cast<Constant*>(argument);
		return constant->getValue()->getiValue();
	}
}

bool Validator::getArgumentBValue(ConstraintArgument* argument, std::vector<std::pair<Variable *, Value *> > values) {
	return false;
}

Value* Validator::getVariableValue(Variable* var, std::vector<std::pair<Variable *, Value *> > values) {
	for (std::pair<Variable *, Value *> current : values) {
		Variable* currentVar = current.first;
		if (currentVar == var || currentVar->getName() == var->getName()) {
			return current.second;
		}
	}
	return NULL;
}

bool Validator::checkComparison(int value, comparison_type CT, int lastValue) {
	switch(CT) {
		case NQ :
			return (value != lastValue);	
		case EQ :
				return (value == lastValue);
			case LQ :
				return (value <= lastValue);
			case LE :
				return (value < lastValue);
			case GQ :
				return (value >= lastValue);
			case GR :
				return (value > lastValue);
		}
}

// Accessor methods
//  


// Other methods
//  


