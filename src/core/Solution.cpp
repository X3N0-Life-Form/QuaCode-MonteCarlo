#include "Solution.h"



Solution::Solution(){

}

std::vector<std::pair<Variable *, Value *> > Solution::getValues(){
  	return values;
}

void Solution::addValue(Variable* var, Value* val) {
	for (std::pair<Variable*, Value*> currentPair : values) {
		if (var->getName() == currentPair.first->getName()) {
			currentPair.second = val;
			break;
		}
	}
}

void Solution::generateValueVector(){
  	for (unsigned int i = 0; i < validator->getProblem()->getVariables().size(); i++) {
  		values.push_back(std::pair<Variable*, Value*>(validator->getProblem()->getVariables()[i], NULL));
  	}
}