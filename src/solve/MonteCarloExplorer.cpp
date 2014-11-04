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
	Validator * val;
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


	for (unsigned int i = 1; i <= problem->getVariables().size();i++) {
		cout << " call randDom" << endl;
		if(problem->getVariables()[i]->getQuantifier() == EXISTS){
			currentSol.addValue(problem->getVariables()[i], randDom(problem->getVariables()[i]) );
		}
		// cflVector is already set to 0 for each variables (constructor of Solution calls generateCflVector())
	}

	nbCfls = currentSol.updateCfl();

	while(true) {
		count++;
		k = currentSol.choice();
		vsauv = currentSol.getValues()[k].second;

		currentSol.addValue(currentSol.getValues()[k].first, randDom(currentSol.getValues()[k].first));

		nNBCfls = currentSol.updateCfl();

		if (nNBCfls > nbCfls) {
			nbCfls = nNBCfls;
		}
		else {
			delta = nbCfls - nNBCfls;
			if(metropolis(delta)) {
				nbCfls = nNBCfls;
			}
			else {
				currentSol.addValue(currentSol.getValues()[k].first, vsauv);
			}
		}
		if (count == frequence) {
			//reordonne for each var (not implemented yet)
			// send to SIBus (not implemented yet)

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


