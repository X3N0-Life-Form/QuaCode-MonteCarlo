
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

/**
 * Looks up an argument's value and stores it in a string.
 * Note: declares a string.
 * @param argument: something(value or values)
 * @param value: whatever is between argument's parenthesises
 */
#define GET_VALUE(argument, value) int leftBracketPos = argument.find("(");\
  int rightBracketPos = argument.find(")");\
  string value = argument.substr(leftBracketPos + 1, rightBracketPos - leftBracketPos - 1);

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
  std::vector<core::Domain*> domains;
  AdapterState state;

  // thread attributes
  boost::thread* thread;
  boost::mutex mutex;
  BoostEvent event;

public:
  // Constructors/Destructors
  SIBusAdapter ( );
  virtual ~SIBusAdapter ( );
  // Getters / Setters
  core::Problem* getProblem();
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
  // Communicate with SIBus
  void sendSolution();
  // Utility methods
  bool doesDomainExist();
};

std::vector<std::string> tokenize(std::string toSplit, std::string token);

#endif // SIBUSADAPTER_H
