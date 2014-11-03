
#ifndef SIBUSADAPTER_H
#define SIBUSADAPTER_H

#include "core/Problem.h"
#include "core/Quantifier.h"
#include "Type.h"
#include "core/factory/VariableFactory.h"
#include "core/Constraint.h"
#include "core/factory/ConstraintFactory.h"
#include "core/Constant.h"

#include <string>
#include <vector>
#include <iostream>

#include <boost/thread.hpp>


enum AdapterState {
  DATA,
  SEARCH,
  EXIT
};

/**
 * Frontend for boost condition variable / mutex.
 * Note: identical to the class of the same name found in SIBus proper.
 */
class BoostEvent {
 private:
  boost::mutex mutex;
  boost::condition_variable boost_cond_var;
  bool signal_status;
 public:
  BoostEvent();
  void signal();
  void wait();
};

/**
 * class SIBusAdapter
 * 
 */
class SIBusAdapter {
private:
  std::istream& input;
  std::ostream& output;
  core::Problem* problem;
  AdapterState state;

  // thread attributes
  boost::thread* thread;
  boost::mutex mutex;

public:
  // Constructors/Destructors
  SIBusAdapter ( );
  virtual ~SIBusAdapter ( );

  // Public Methods
  //
  void dealWithInput();
  void dealWithInputData(std::string line);
  void dealWithInputSearch(std::string line);
  // Variable construction
  Quantifier identifyQuantifier(std::string s_quant);
  Type identifyType(std::string s_type);
  core::Domain* identifyDomain(std::string s_domain);
  // Constraint construction
  core::constraint_type identifyConstraintType(std::string type);
  core::comparison_type identifyComparisonType(std::string type);
  core::ConstraintArgument* identifyConstraintArgument(std::string argument);
  // Thread handling
  void run();

};

std::vector<std::string> tokenize(std::string toSplit, std::string token);

#endif // SIBUSADAPTER_H
