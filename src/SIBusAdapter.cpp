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
  string word;
  input >> word;
  if (line == "VAR_BINDER") {
    //TODO: use tokenize() here as well
    // VAR_BINDER = var(quant,type,name,domain)
    int posLeft = word.find("(");
    int posEndQuant = word.find(",", posLeft);
    int posEndType = word.find(",", posEndQuant + 1);
    int posEndName = word.find(",", posEndType + 1);
    int posRight = word.find(")");
    // extract values
    string s_quant = word.substr(posLeft + 1, posEndQuant - posLeft);
    string s_type = word.substr(posEndQuant + 1, posEndType - posEndQuant);
    string name = word.substr(posEndType + 1, posEndName - posEndType);
    string s_domain = word.substr(posEndName + 1, posRight - posEndName);
    // convert values
    Quantifier quant = identifyQuantifier(s_quant);
    Type type = identifyType(s_type);
    Domain* domain = identifyDomain(s_domain);
    // create & store
    Variable* var = VariableFactory::createVariable(quant, type, name, domain);
    problem->addVariable(var);
  } else if (line == "VAR_AUX") {
    vector<string> tokens = tokenize(line, " ");
    Quantifier quant = identifyQuantifier(tokens[0]);
    Type type = identifyType(tokens[1]);
    string name = tokens[2];
    Variable* var = VariableFactory::createVariable(quant, type, name);
    problem->addVariable(var);
  } else if (line == "CONSTRAINT") {
    vector<string> tokens = tokenize(line, " ");
    unsigned int i = 2;
    constraint_type constraintType = identifyConstraintType(tokens[0]);
    comparison_type comparisonType = identifyComparisonType(tokens[1]);
    Constraint* constraint = ConstraintFactory::createConstraint(constraintType, comparisonType);
    for ( ;i < tokens.size(); i++) {
      ConstraintArgument* argument = identifyConstraintArgument(tokens[i]);
      constraint->addArgument(argument);
    }
    problem->addConstraint(constraint);
  } else if (line == "VAR_ARRAY_BINDER") {
    throw "not implemented";
  } else if (line == "VAR_ARRAY_AUX") {
    throw "not implemented";
  } else {
    cerr << "Unrecognized data input: " << line << endl;
  }
}

ConstraintArgument* SIBusAdapter::identifyConstraintArgument(string argument) {
  GET_VALUE(argument, s_value) // string s_value
  if (argument.find("var") != string::npos) {
    Variable* variable = problem->getVariable(s_value);
    if (variable != NULL) {
      return variable;
    } else {
      cerr << "Constraint argument error: unknown variable " << s_value << endl;
      return NULL;
    }
  } else if (argument.find("int") != string::npos) {
    Value* value = new Value(stoi(s_value));
    return new Constant(value);
  } else if (argument.find("1") != string::npos) {
    if (s_value == "true") {
      return new Constant(new Value(true));
    } else {
      return new Constant(new Value(false));
    }
  } else if (argument.find("interval") != string::npos) {
    vector<string> bound = tokenize(s_value, ",");
    int lowerBoundary = stoi(bound[0]);
    int upperBoundary = stoi(bound[1]);
    Domain* domain = problem->getDomain(lowerBoundary, upperBoundary);//TODO: get that checked out
    if (domain != NULL) {
      return domain;
    } else {
      cerr << "Constraint argument warning: unknown domain " << s_value << endl;
      return new Domain(lowerBoundary, upperBoundary);
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
    throw string("Unrecognised quantifier: ").append(s_quant);
  }
}

Type SIBusAdapter::identifyType(string s_type) {
  if (s_type == "I") {
    return INTEGER;
  } else if (s_type == "B") {
    return BOOLEAN;
  } else {
    throw string("Unrecognized type: ").append(s_type);
  }
}

Domain* SIBusAdapter::identifyDomain(string s_domain) {
  GET_VALUE(s_domain, s_value); // string s_value
  vector<string> bound = tokenize(s_value, ",");
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
    throw string("Unrecognised constraint type: ").append(type);
  }
}

comparison_type SIBusAdapter::identifyComparisonType(std::string type) {
  if (type == string("NQ")) {
    return NQ;
  } else if (type == string("EQ")) {
    return EQ;
  } else if (type == string("LQ")) {
    return LQ;
  } else if (type == string("LE")) {
    return LE;
  } else if (type == string("GQ")) {
    return GQ;
  } else if (type == string("GR")) {
    return GR;
  } else {
    throw string("Unrecognised comparison type: ").append(type);
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

void SIBusAdapter::sendSolution() {
  // /!\ Note: this is a method stub
  output << "SOLUTION         = ";
  // Transmit variables & their associated values
  for (int i = 0; i < 10; i++) {
    output << " var(" << "name" << "," << "value" << ")";
  }
  // Transmit additional information?
  
}

//
// Other Functions
//

vector<string> tokenize(string toSplit, string token) {
  int pos;
  vector<string> result;
  while ((pos = toSplit.find(token)) != string::npos) {
    string nuString = toSplit.substr(0, pos);
    result.push_back(nuString);
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
