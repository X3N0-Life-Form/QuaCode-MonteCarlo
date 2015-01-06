#include "Solution.h"

using namespace std;
using namespace core;

Solution::Solution(Validator * val){
	
	validator = val;
	generateValueVector();
	//generateCflVector();
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
			currentPair.second->copy(val);
			break;
		}
	}
}

void Solution::modifValue(int index, Value* val) {
	values[index].second = val;
}

void Solution::generateValueVector(){
  	for (unsigned int i = 0; i < validator->getProblem()->getVariables().size(); i++) {
		Value* v = new Value(0);
  		values.push_back(std::pair<Variable*, Value*>(validator->getProblem()->getVariables()[i], v));
		  
  	}
}





 int Solution::updateCfl(Problem* problem) {
 	int cmp = 0;

 	for (unsigned int i = 0; i < validator->getProblem()->getConstraints().size(); i++) {
		Constraint* constraint = validator->getProblem()->getConstraints()[i];
 		if (!validator->validateConstraint(constraint, values)) {
 			cmp++;
 			for (unsigned int j = 0; j < constraint->getArguments().size(); j++){
 				increment(constraint->getArguments()[j], problem);
 			}
 		}
 	} 	
	return cmp;
 }

 
//TODO mass refactoring
void Solution::increment(ConstraintArgument * arg, Problem* problem) {
 	// check if is variable
 	// if yes => update
 	Variable * test = dynamic_cast<Variable *>(arg);
 	if(test != NULL) {
	 	for (unsigned int i = 0; i < values.size(); i++) {
	 		if (values[i].first->getName() == test->getName() && values[i].first->getDomain() != NULL) {
	 			values[i].first->getDomain()->incrementCfl(values[i].second->getiValue());
	 			break;
	 		} else if (values[i].first->getName() == test->getName()) {
				// auxilliary variables require special treatment, so get the constraint that defines it	
				for (Constraint* constraint : problem->getConstraints()) {
					Variable* lastArg = dynamic_cast<Variable*>(constraint->getArguments().back());
					if (constraint->getComparisonType() == EQ
						&& lastArg != NULL
						&& lastArg->getName() == values[i].first->getName())
					{
						// once you've found it, update the cfl of the variables composing it
						for (unsigned int j = 0; j < constraint->getArguments().size() - 1; j++) {
							Variable* currentVar = dynamic_cast<Variable*>(constraint->getArguments()[j]);
							if (currentVar != NULL) {
								unsigned int pos = 0;
								for (unsigned int k = 0; k < values.size(); k++) {//TODO refactor that into another method
									if (values[k].first->getName() == currentVar->getName()) {
										pos = k;
										break;
									}
								}
								currentVar->getDomain()->incrementCfl(values[pos].second->getiValue());
							}
						} // end for each argument in constraint
						break;
					}
				} // end for each constraint
			}
	 	}
 	}
 }

 

int Solution::choice() {
 	int cflVal = 0;
 	int index = 0;
 	int temp = 0;
	for (unsigned int i = 0; i < values.size(); i++) {
		if (values[i].first->getDomain() != NULL) {
			cflVal = values[i].first->getDomain()->totalCfl();
			index = i;
			break;
		}
	}

 	for (unsigned int i = 1; i < values.size(); i++) {
		if (values[i].first->getDomain() != NULL) {
	 		temp = values[i].first->getDomain()->totalCfl();
	 		if(temp < cflVal) {
	 			index = i;
	 			cflVal = temp;
	 		} else if (temp == cflVal) {
				double randValue = rand() % 10;
				if (randValue > 5) {
					index = i;
				}
			}
		}
	}
	return index;
}
