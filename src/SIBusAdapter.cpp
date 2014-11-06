#include "SIBusAdapter.h"

using namespace std;
using namespace core;
//using namespace solve;

// Constructors/Destructors
//  

SIBusAdapter::SIBusAdapter ( ) : input(cin), output(cout), state(DATA) {
  problem = new Problem();
  thread = new boost::thread(&SIBusAdapter::run, this);
}

SIBusAdapter::~SIBusAdapter ( ) {
  mutex.lock();
  state = EXIT;
  event.signal();
  // gotta be careful not to unlock something that has never been locked
  if (mutex.try_lock()) //fishy
    mutex.unlock();
  thread->join();
  delete(thread);
  delete(problem);
}

//
// Getters / Setters
//

Problem* SIBusAdapter::getProblem() {
  return problem;
}

//  
// Methods
//  

void SIBusAdapter::dealWithInput() {
  string line;
  input >> line;
  switch (state) {
  case DATA:
    dealWithInputData(line);
    break;
  case SEARCH:
    dealWithInputSearch(line);
    break;
  case EXIT:
    return;
  }
  
}

void SIBusAdapter::dealWithInputData(string line) {
  vector<string> tokens = tokenize(line, " ");
  if (line.find("VAR_BINDER") != string::npos) {
    // VAR_BINDER = var(quant,type,name,domain)
    // extract values
    GET_VALUE(tokens[2], s_var_params);
    vector<string> var_params = tokenize(s_var_params, ",");
    string s_quant = var_params[0];
    string s_type = var_params[1];
    string name = var_params[2];
    string s_domain = var_params[3];
    // convert values
    Quantifier quant = identifyQuantifier(s_quant);
    Type type = identifyType(s_type);
    Domain* domain = identifyDomain(s_domain);
    // create & store
    Variable* var = VariableFactory::createVariable(quant, type, name, domain);
    problem->addVariable(var);
  } else if (line.find("VAR_AUX") != string::npos) {
    GET_VALUE(tokens[2], s_var_params);
    vector<string> var_params = tokenize(s_var_params, ",");
    Quantifier quant = identifyQuantifier(var_params[0]);
    Type type = identifyType(var_params[1]);
    string name = var_params[2];
    Variable* var = VariableFactory::createVariable(quant, type, name);
    problem->addVariable(var);
  } else if (line.find("CONSTRAINT") != string::npos) {
    unsigned int i = 4;
    constraint_type constraintType = identifyConstraintType(tokens[2]);
    comparison_type comparisonType = identifyComparisonType(tokens[3]);
    Constraint* constraint = ConstraintFactory::createConstraint(constraintType, comparisonType);
    for ( ;i < tokens.size(); i++) {
      ConstraintArgument* argument = identifyConstraintArgument(tokens[i]);
      constraint->addArgument(argument);
    }
    problem->addConstraint(constraint);
  } else if (line.find("VAR_ARRAY_BINDER") != string::npos) {
    throw "not implemented";
  } else if (line.find("VAR_ARRAY_AUX") != string::npos) {
    throw "not implemented";
  } else {
    cerr << "Warning: Unrecognized data input: " << line << endl;
  }
}

ConstraintArgument* SIBusAdapter::identifyConstraintArgument(string argument) {
  GET_VALUE(argument, s_value) // string s_value
  if (argument.find("var") != string::npos) {
    Variable* variable = problem->getVariable(s_value);
    if (variable != NULL) {
      return variable;
    } else {
      throw string("Error: unknown variable in constraint argument: ").append(s_value);
    }
  } else if (argument.find("interval") != string::npos) {
    vector<string> bound = tokenize(s_value, ":");
    int lowerBoundary = stoi(bound[0]);
    int upperBoundary = stoi(bound[1]);
    Domain* domain = problem->getDomain(lowerBoundary, upperBoundary);
    if (domain != NULL) {
      return domain;
    } else {
      //cerr << "Constraint argument warning: unknown domain " << s_value << endl;
      return new Domain(lowerBoundary, upperBoundary);
    }
  } else if (argument.find("int") != string::npos) {
    Value* value = new Value(stoi(s_value));
    return new Constant(value);
  } else if (argument.find("1") != string::npos) {
    if (s_value == string("true")) {
      return new Constant(new Value(true));
    } else {
      return new Constant(new Value(false));
    }
  } else {
    return NULL; // could not identify argument
  }
}

Quantifier SIBusAdapter::identifyQuantifier(string s_quant) {
  if (s_quant == "E") {
    return EXISTS;
  } else if (s_quant == "F") {
    return FORALL;
  } else {
    throw string("Error: Unrecognised quantifier: ").append(s_quant);
  }
}

Type SIBusAdapter::identifyType(string s_type) {
  if (s_type == "I") {
    return INTEGER;
  } else if (s_type == "B") {
    return BOOLEAN;
  } else {
    throw string("Error: Unrecognized type: ").append(s_type);
  }
}

Domain* SIBusAdapter::identifyDomain(string s_domain) {
  GET_VALUE(s_domain, s_value); // string s_value
  vector<string> bound = tokenize(s_value, ":");
  if (bound.size() != 2) {
    throw string("Error: malformated domain: ").append(s_domain);
  }
  int lowerBoundary = stoi(bound[0]);
  int upperBoundary = stoi(bound[1]);
  // does that domain exist?
  for (Domain* currentDomain : domains) {
    if (currentDomain->getFirstValue() == lowerBoundary
	&& currentDomain->getLastValue() == upperBoundary)
      return currentDomain;
  }
  // if not, create it
  Domain* domain = new Domain(lowerBoundary, upperBoundary);
  domains.push_back(domain);
  return domain;
  
}

constraint_type SIBusAdapter::identifyConstraintType(std::string type) {
  if (type == string("AND")) {
    return AND;
  } else if (type == string("OR")) {
    return OR;
  } else if (type == string("XOR")) {
    return XOR;
  } else if (type == string("IMP")) {
    return IMP;
  } else if (type == string("EQ")) {
    return C_EQ;
  } else if (type == string("TIMES")) {
    return TIMES;
  } else if (type == string("LINEAR")) {
    return LINEAR;
  } else if (type == string("RE_AND")) {
    return RE_AND;
  } else if (type == string("RE_OR")) {
    return RE_OR;
  } else if (type == string("RE_IMP")) {
    return RE_IMP;
  } else if (type == string("RE_EQ")) {
    return RE_EQ;
  } else if (type == string("RE_TIMES")) {
    return RE_TIMES;
  } else if (type == string("RE_LINEAR")) {
    return RE_LINEAR;
  } else if (type == string("ELEMENT")) {
    return ELEMENT;
  } else {
    throw string("Error: Unrecognised constraint type: ").append(type);
  }
}

comparison_type SIBusAdapter::identifyComparisonType(std::string type) {
  if (type == string("_NQ_")) {
    return NQ;
  } else if (type == string("_EQ_")) {
    return EQ;
  } else if (type == string("_LQ_")) {
    return LQ;
  } else if (type == string("_LE_")) {
    return LE;
  } else if (type == string("_GQ_")) {
    return GQ;
  } else if (type == string("_GR_")) {
    return GR;
  } else {
    throw string("Error: Unrecognised comparison type: ").append(type);
  }
}

void SIBusAdapter::dealWithInputSearch(string line) {//TODO
  string word;
  input >> word;
  if (word == "CHOICE") {

  } else if (word == "FAIL") {

  } else if (word == "SUCCESS") {

  } else {

  }
}

//
// Thread Methods
//

void SIBusAdapter::run() {
  while (state != EXIT) {
    mutex.lock();
    //manage event

    mutex.unlock();
    event.wait();
  }
  mutex.unlock();
}

//
// Communicate with SIBus
//

void SIBusAdapter::sendSolution(Solution* solution) {
  // /!\ Note: this is a method stub
  output << "SOLUTION         = ";
  // Transmit variables & their associated values
  for (pair<Variable*, Value*> currentPair : solution->getValues()) {
    output << " val(" << currentPair.first->getName() << ","
	   << currentPair.second->getValueAsString() << ")";
  }
  // Transmit additional information?
  
  // End of transmission
  output << endl;
}

//
// Other Functions
//

vector<string> tokenize(string toSplit, string token) {
  int pos;
  vector<string> result;
  while ((pos = toSplit.find(token)) != string::npos) {
    string nuString = toSplit.substr(0, pos);
    if (!nuString.empty()) {
      result.push_back(nuString);
    }
    toSplit = toSplit.substr(pos + 1);
  }
  result.push_back(toSplit);
  return result;
}

//
// BoostEvent
//
BoostEvent::BoostEvent() : signal_status(false) {}

void BoostEvent::signal() {
  boost::lock_guard<boost::mutex> lock(mutex);
  signal_status = true;
  boost_cond_var.notify_one();
}

void BoostEvent::wait() {
  boost::unique_lock<boost::mutex> lock(mutex);
  while (!signal_status) {
    boost_cond_var.wait(lock);
  }
  signal_status = false;
}
