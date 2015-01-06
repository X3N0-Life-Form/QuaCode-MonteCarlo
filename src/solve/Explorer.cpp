#include "Explorer.h"

using namespace solve;



Explorer::Explorer ( ) {
}

Explorer::~Explorer ( ) { }

void Explorer::setAdapter(SIBusAdapter* adapter) {
  this->adapter = adapter;
}

int Explorer::getArgumentValue(ConstraintArgument* arg, Solution& sol) {
	Variable* var = dynamic_cast<Variable*>(arg);
	if (var != NULL) {
		for (std::pair<Variable *, Value *> current : sol.getValues()) {
			if (current.first->getName() == var->getName()) {
				return current.second->getiValue();
			}
		}
	} else { // is a constant
		Constant* cst = dynamic_cast<Constant*>(arg);
		return cst->getValue()->getiValue();
	}
}
