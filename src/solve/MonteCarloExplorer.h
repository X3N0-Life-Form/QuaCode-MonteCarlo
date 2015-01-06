
#ifndef MONTECARLOEXPLORER_H
#define MONTECARLOEXPLORER_H
#include "Explorer.h"
#include "../core/Domain.h"
#include "../core/Value.h"
#include "../core/Problem.h"
#include "../core/Variable.h"
#include "../Type.h"
#include "IntegerValidator.h"
#include "BooleanValidator.h"

#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <cstdlib> // rand()
#include <iostream>




namespace solve {

/**
  * class MonteCarloExplorer
  * 
  */
class MonteCarloExplorer : public Explorer {

private:
  double temperature;
  int frequence;
  Problem * problem; // contains nbVar, variables, domains, constraints

public:
  
  // Constructors/Destructors
  // 
  MonteCarloExplorer(Problem * prob);
  virtual ~MonteCarloExplorer ( );
  ///////////////////////////////////////
  /////////// getters & setters /////////
  ///////////////////////////////////////

  double getTemperature();
  int getFrequence();


  ///////////////////////////////////////////
  //////// Methods///////////////////////////
  ///////////////////////////////////////////
  // Monte Carlo
  virtual int heuristic();

  // rand(Di)
  Value * randDom(Variable* var);

  // Metropolis acceptance rule
  bool metropolis(int delta);

  void decreaseTemperature();

  void initAuxValues(Solution& sol);
  void calculateAuxValue(Variable* var, Solution& sol);
  void hasConstraintWithAuxVar(Variable* var, Solution& sol);

  void calculateDifferencesAndSendSwapAsk(Variable* var, std::vector<std::pair<int, int> > oldCfl, std::vector<std::pair<int, int> > newCfl);//TODO: put that in Explorer?

};
}; // end of package namespace

#endif // MONTECARLOEXPLORER_H
