
#ifndef MONTECARLOEXPLORER_H
#define MONTECARLOEXPLORER_H
#include "Explorer.h"
#include "../core/Domain.h"
#include "../core/Value.h"
#include "../core/Problem.h"
#include "../core/Variable.h"
#include "../Type.h"
#include "../core/Solution.h"
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
  int heuristic();

  // rand(Di)

  Value * randDom(Variable* var);

  // Metropolis acceptance rule
  bool metropolis(int delta);

  void decreaseTemperature();

};
}; // end of package namespace

#endif // MONTECARLOEXPLORER_H
