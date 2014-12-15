#include "Solution.h"

using namespace std;
using namespace core;

Solution::Solution(Validator * val){
	generateValueVector();
	//generateCflVector();
	validator = val;
}

std::vector<std::pair<Variable *, Value *> > Solution::getValues(){
  	return values;
}
/*
std::vector<std::pair<Variable *, int> >  Solution::getCfl(){
	return cfl;
}*/

void Solution::addValue(Variable* var, Value* val) {
	for (std::pair<Variable*, Value*> currentPair : values) {
		if (var->getName() == currentPair.first->getName()) {
			currentPair.second = val;
			break;
		}
	}
}

void Solution::modifValue(int index, Value* val) {
	values[index].second = val;
}

void Solution::generateValueVector(){
  	for (unsigned int i = 0; i < validator->getProblem()->getVariables().size(); i++) {
  		values.push_back(std::pair<Variable*, Value*>(validator->getProblem()->getVariables()[i], NULL));
  	}
}





 int Solution::updateCfl() {
 	int cmp = 0;

 	for (unsigned int i = 0; i < validator->getProblem()->getConstraints().size(); i++) {
 		if (!validator->validateConstraint(validator->getProblem()->getConstraints()[i], values)) {
 			cmp++;
 			for (unsigned int j = 0; j < validator->getProblem()->getConstraints()[i]->getArguments().size(); j++){
 				increment(validator->getProblem()->getConstraints()[i]->getArguments()[j]);
 				break;
 			}
 		}
 	} 	
	return cmp;
 }

 

 void Solution::increment(ConstraintArgument * arg) {
 	// check if is variable
 	// if yes => update
 	Variable * test = dynamic_cast<Variable *>(arg);
 	if(test != NULL) {
	 	for (unsigned int i = 0; i < values.size();i++) {
	 		if (values[i].first == arg) {
	 			values[i].first->getDomain()->incrementCfl(values[i].second->getiValue());
	 			break;
	 		}
	 	}
 	}
 }

 

 int Solution::choice(){
 	int cflVal = values[0].first->getDomain()->totalCfl();
 	int index = 0;
 	int temp = 0;
 	for (unsigned int i = 1; i < values.size(); i++) {
 		temp = values[i].first->getDomain()->totalCfl();
 		if(temp < cflVal) {
 			index = i;
 			cflVal = temp;
 		}
 	}
 	return index;
 }
