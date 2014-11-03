#include "Solution.h"

using namespace std;

Solution::Solution(){

}

std::vector<std::pair<Variable *, Value *> > Solution::getValues(){
  	return values;
}

std::vector<std::pair<Variable *, int> >  Solution::getCfl(){
	return cfl;
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


void Solution::generateCflVector(){
	for (unsigned int i = 0; i < validator->getProblem()->getVariables().size(); i++) {
		cfl.push_back(std::pair<Variable *, int>(validator->getProblem()->getVariables()[i], 0));
	}
}

 void Solution::initCfl() {
 	for (unsigned int i = 0; i < values.size();i++){
 		cfl[i].second = 0;
 	}
 }

 int Solution::updateCfl() {
 	int cmp = 0;

 	for (unsigned int i = 0; i < validator->getProblem()->getConstraints().size(); i++) {
 		if (!validator->validateConstraint(validator->getProblem()->getConstraints()[i], values)) {
 			cmp++;
 			//TODO : update each cfl for each variables
 			for (unsigned int j = 0; j < validator->getProblem()->getConstraints()[i]->getArguments().size(); j++) {
 				incrementCfl(validator->getProblem()->getConstraints()[i]->getArguments()[j]);
 				break;
 			}		
 		}
 	} 	
	return cmp;
 }

 void Solution::incrementCfl(ConstraintArgument * arg) {
 	for (unsigned int i = 0; i < cfl.size();i++) {
 		if (cfl[i].first == arg) {
 			cfl[i].second++;
 			break;
 		}
 	}
 }