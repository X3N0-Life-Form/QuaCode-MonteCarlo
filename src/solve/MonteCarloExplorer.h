
#ifndef MONTECARLOEXPLORER_H
#define MONTECARLOEXPLORER_H
#include "Explorer.h"

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

class MonteCarloExplorer : public Explorer
{

private:
  double temperature;
  int frequence;
  Problem * problem; // contains nbVar, variables, domains, constraints

public:

  // Constructors/Destructors
  // 
  MonteCarloExplorer();

  /////////// getters & setters ///////////
  ///////////////////////////////////////

double getTemperature();

int getFrequence();


  ///////////////////////////////////////////
  //////// Methods///////////////////////////
  ///////////////////////////////////////////
  // Monte Carlo
  void heuristic();

  // rand(Di)

  int randDom(Domain dom);

  // Metropolis acceptance rule
  bool metropolis(int delta);

  void decreaseTemperature();

  /**
   * Empty Destructor
   */
  virtual ~MonteCarloExplorer ( );



  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};
}; // end of package namespace

#endif // MONTECARLOEXPLORER_H
