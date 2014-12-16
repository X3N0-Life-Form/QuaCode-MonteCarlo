
#ifndef SIBUSADAPTER_H
#define SIBUSADAPTER_H

#include "core/Problem.h"
#include "core/Quantifier.h"
#include "Type.h"
#include "core/factory/VariableFactory.h"
#include "core/Constraint.h"
#include "core/factory/ConstraintFactory.h"
#include "core/Constant.h"
#include "core/Solution.h"
#include "AdapterException.h"

#include <string>
#include <vector>
#include <iostream>

#include <boost/thread.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

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

//#define VectorStream boost::interprocess::basic_vectorstream<boost::interprocess::string> 

/**
 * class SIBusAdapter
 * 
 */
class SIBusAdapter {
private:
  // communication attributes
  //std::istream& input;
  //std::ostream& output;
  //VectorStream vectorStream;
  boost::interprocess::message_queue input;
  boost::interprocess::message_queue output;

  // problem building attributes
  core::Problem* problem;
  std::vector<core::Domain*> domains;
  AdapterState state;

  // thread attributes
  boost::thread* thread;
  boost::mutex mutex;
  BoostEvent event;

  // options
  bool displayWarnings;

public:
  // static const attributes
  //
  //static const char* SEGMENT_NAME;
  //static const int SEGMENT_SIZE;
  static const char* IPC_NAME_TO_ADAPTER;
  static const char* IPC_NAME_FROM_ADAPTER;
  static const int MAX_MESSAGES;
  static const int MESSAGE_SIZE;
  // Constructors/Destructors
  //
  SIBusAdapter();
  //SIBusAdapter(streambuf* inputBuffer, streambuf* outputBuffer);
  virtual ~SIBusAdapter();
  // Getters / Setters
  //
  core::Problem* getProblem();
  //std::istream& getInput();
  //std::ostream& getOutput();
  boost::interprocess::message_queue& getInput();
  boost::interprocess::message_queue& getOutput();
  void setDisplayWarnings(bool displayWarnings);
  AdapterState getState();
  // dealWithInput methods
  //
  void dealWithInput();
  void dealWithInputData(std::string line);
  void dealWithInputSearch(std::string line);
  // Variable construction
  //
  Quantifier identifyQuantifier(std::string s_quant);
  Type identifyType(std::string s_type);
  core::Domain* identifyDomain(std::string s_domain);
  // Constraint construction
  //
  core::constraint_type identifyConstraintType(std::string type);
  core::comparison_type identifyComparisonType(std::string type);
  core::ConstraintArgument* identifyConstraintArgument(std::string argument);
  // Thread handling
  //
  void run();
  // Communicate with SIBus
  //
  void sendSolution(core::Solution* solution);
  void sendSwapAsk(core::Variable* var, const core::Value& val1, const core::Value& val2);
  // Utility methods
  //
  void printWarning(std::string message);
  void printWarning(std::string message, std::string line);
};

std::vector<std::string> tokenize(std::string toSplit, std::string token);

#endif // SIBUSADAPTER_H
