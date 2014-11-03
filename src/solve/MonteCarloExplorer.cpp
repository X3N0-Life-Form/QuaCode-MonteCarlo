#include "MonteCarloExplorer.h"

using namespace solve;
using namespace std;

// Constructors/Destructors
//  


MonteCarloExplorer::MonteCarloExplorer ( ) {
	temperature = 4.5;
	frequence = 1000;
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

void MonteCarloExplorer::heuristic() {
	srand(time(NULL));
	for (unsigned int i = 1; i <= problem->getVariables().size();i++) {
		cout << " call randDom" << endl;
		// problem with randDom type
		//problem->addValue(problem->getVariables()[i], randDom(problem->getVariables()[i].getDomain()) );

		// for(unsigned int k = 1; k <= )
	}

	//metropolis(5);
}

// RANDOM VALUE => random initialisation for each variables
	// NOTE : this is very basic => next step : find how to exclude some values (the ones already tested)
	// SECOND NOTE : test if it works
	// must be of type Value (I guess)
Value MonteCarloExplorer::randDom(Variable* var) {
	Domain* dom = var->getDomain();
	Type type = var->getType();
	if(type==INTEGER){
		while(true) {
			int valueInt = rand() % (dom->getLastValue() - dom->getFirstValue() + 1) + dom->getFirstValue();
			if (!dom->alreadyInto(valueInt)){
				return Value(valueInt);
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
				return Value(b);
			}
		}
		
	}
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


