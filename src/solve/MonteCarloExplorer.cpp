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

	//metropolis(5);
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


