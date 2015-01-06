#include "MonteCarloExplorer.h"

using namespace solve;
using namespace std;
using namespace core;

// Constructors/Destructors
//  


MonteCarloExplorer::MonteCarloExplorer (Problem * prob ) {
	temperature = 4.5;
	frequence = 1000;
	problem = prob;
	// problem is set with SIBus adapter
}

MonteCarloExplorer::~MonteCarloExplorer ( ) { }

////////////////////////////////
///// getters & setters ////////
////////////////////////////////

double MonteCarloExplorer::getTemperature() {
	return temperature;
}

int MonteCarloExplorer::getFrequence() {
	return frequence;
}



///////////////////
// Methods/////////
///////////////////

// MONTE-CARLO ALGORITHM //

int MonteCarloExplorer::heuristic() {
	srand(time(NULL));

	// declaration of val 
	int ok = 0;
	Validator * val = NULL;
	for (unsigned int i = 0; i < problem->getVariables().size(); i++){
		if (problem->getVariables()[i]->getType() == BOOLEAN){
			val = new BooleanValidator(problem);
			ok = 1;
			break;
		}
		else if (problem->getVariables()[i]->getType() == INTEGER){
			val = new IntegerValidator(problem);
			ok = 1;
			break;
		}
	}
	//if error
	if (ok == 0){
		return 0;
	}
	//////////////////////////
	// many declarations /////
	//////////////////////////
	Solution currentSol(val);
	Solution savedSol(val);
	int count = 0;
	int nbCfls = 0;
	int nNBCfls = 0;
	int k = -1;
	int delta = 0;
	Value * vsauv;


	for (unsigned int i = 0; i < problem->getVariables().size(); i++) {
		Variable* var = problem->getVariables()[i];
		if (var->getDomain() != NULL) {
			Value* randomValue = randDom(var);
			currentSol.addValue(var, randomValue);
			delete(randomValue);
		}
		// cflVector is already set to 0 for each variables (constructor of Solution calls generateCflVector())
	}
	initAuxValues(currentSol);

	nbCfls = currentSol.updateCfl(problem);

	while(adapter->getState() != EXIT) {
		count++;
		k = currentSol.choice();
		vsauv = currentSol.getValues()[k].second;

		Variable* var = currentSol.getValues()[k].first;
		currentSol.addValue(var, randDom(var));
		hasConstraintWithAuxVar(var, currentSol);
		nNBCfls = currentSol.updateCfl(problem);

		if (nNBCfls > nbCfls) {
			nbCfls = nNBCfls;
		}
		else {
			delta = nbCfls - nNBCfls;
			if(metropolis(delta)) {
				nbCfls = nNBCfls;
			}
			else {
				currentSol.addValue(var, vsauv);
				hasConstraintWithAuxVar(var, currentSol);
			}
		}
		if (count == frequence) {
			for (std::pair<Variable*, Value*> currentPair : currentSol.getValues()) {
				if (currentPair.first->getDomain() != NULL) {
					vector<pair<int, int> > sortedCfl = currentPair.first->getDomain()->sortedCfl();
					calculateDifferencesAndSendSwapAsk(currentPair.first->getDomain()->getCfl(), sortedCfl);
					//adapter->sendDomain(currentPair.first, sortedCfl);
				}
			}

			count = 0;
		}
	}

	return 1;
}

// RANDOM VALUE => random initialisation for each variables
	// NOTE : this is very basic => next step : find how to exclude some values (the ones already tested)
	// SECOND NOTE : test if it works
	// must be of type Value (I guess)
Value * MonteCarloExplorer::randDom(Variable* var) {
	Domain* dom = var->getDomain();
	Type type = var->getType();
	if(type==INTEGER){
		while(true) {
			int valueInt = rand() % (dom->getLastValue() - dom->getFirstValue() + 1) + dom->getFirstValue();
			if (!dom->alreadyInto(valueInt)){
				return new Value(valueInt);
			}
		}
	}
	if(type==BOOLEAN){			
		while(true) {
			int valueBool = rand() % 1;
			bool b;
				if(valueBool==0)
					b=false;
				else b=true;
			if (!dom->alreadyInto(valueBool)){			
				return new Value(b);
			}
		}		
	}
	cout << "WE SHOULD NOT BE HERE (randDom)" << endl;
	return NULL;
}



// METROPOLIS ACCEPTANCE RULE - SA //
	/*	true => acceptance else false
	 	delta will be (the current state - the new state) => if the new one has more conflicts then it becomes the current state */
bool MonteCarloExplorer::metropolis(int delta){
	double value = exp(delta / temperature);
	double randValue = rand() % 10;
	if (delta < 0 || value > randValue) {
		decreaseTemperature();
		return true;
	}
	else {
		decreaseTemperature();
		return false;
	}
}

// used to decrease temperature into metropolis
void MonteCarloExplorer::decreaseTemperature() {
	temperature = temperature * 0.98;
}


void MonteCarloExplorer::initAuxValues(Solution& sol) {
	for (Variable* var : problem->getVariables()) {
		if (var->getDomain() == NULL) {
			calculateAuxValue(var, sol);
		}
	}
}

void MonteCarloExplorer::calculateAuxValue(Variable* var, Solution& sol) {
	for (Constraint* constraint : problem->getConstraints()) {
		Variable* lastArg = dynamic_cast<Variable*>(constraint->getArguments().back());
		if (constraint->getComparisonType() == EQ
			&& lastArg != NULL && lastArg->getName() == var->getName())
		{
			int res = 0;
			switch (constraint->getConstraintType()) {
				case LINEAR:
					res = 0;
					for (unsigned int i = 0; i < constraint->getArguments().size() - 1; i = i + 2) {
						Constant* cst = dynamic_cast<Constant*>(constraint->getArguments()[i]);
						Variable* arg = dynamic_cast<Variable*>(constraint->getArguments()[i + 1]);
						res += getArgumentValue(arg, sol) * cst->getValue()->getiValue();
					}
					break;
				case TIMES:
					res = 1;
					for (unsigned int i = 0; i < constraint->getArguments().size() - 1; i++) {
						ConstraintArgument* arg = constraint->getArguments()[i];
						res *= getArgumentValue(arg, sol);
					}
					break;
				default:
					cout << "WARNING: not implemented (MonteCarloExplorer::calculateAuxValue)" << endl;
					break;
			}
			sol.addValue(var, new Value(res));
			break;
		}
	}
}

void MonteCarloExplorer::hasConstraintWithAuxVar(Variable* var, Solution& sol) {
	for (Constraint* constraint : problem->getConstraints()) {
		for (ConstraintArgument* arg : constraint->getArguments()) {
			Variable* currentVar = dynamic_cast<Variable*>(arg);
			if (currentVar != NULL && currentVar->getName() == var->getName()) {
				Variable* lastArg = dynamic_cast<Variable*>(constraint->getArguments().back());
				if (lastArg != NULL && lastArg->getDomain() == NULL) {//TODO: change that kind of test into Variable.isVarAux()
					calculateAuxValue(lastArg, sol);
				}
			}
		}
	}
}

void MonteCarloExplorer::calculateDifferencesAndSendSwapAsk(std::vector<std::pair<int, int> > oldCfl, std::vector<std::pair<int, int> > newCfl) {
	for (int i = 0; i < oldCfl.size(); i++) {
		if (oldCfl[i].first != newCfl[i].first) {
			//for
		}
	}
}

