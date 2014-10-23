
#ifndef SIBUSADAPTER_H
#define SIBUSADAPTER_H

#include "core/Problem.h"
#include "core/Quantifier.h"
#include "Type.h"
#include "core/factory/VariableFactory.h"
#include "core/Constraint.h"

#include <string>
#include <vector>
#include <iostream>


enum AdapterMode {
  DATA,
  SEARCH
};

/**
  * class SIBusAdapter
  * 
  */

class SIBusAdapter
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  SIBusAdapter ( );

  /**
   * Empty Destructor
   */
  virtual ~SIBusAdapter ( );

  // Public Methods
  //
  void dealWithInput();
  void dealWithInputData(std::string line);
  void dealWithInputSearch(std::string line);
  
  Quantifier identifyQuantifier(std::string s_quant);
  Type identifyType(std::string s_type);
  core::Domain* identifyDomain(std::string s_domain);

  core::constraint_type identifyConstraintType(std::string type);
  core::comparison_type identifyComparisonType(std::string type);
private:

  // Static Private attributes
  //  

  // Private attributes
  //  
  std::istream& input;
  std::ostream& output;
  core::Problem* problem;
  AdapterMode mode;

};

std::vector<std::string> tokenize(std::string toSplit, std::string token);

#endif // SIBUSADAPTER_H
