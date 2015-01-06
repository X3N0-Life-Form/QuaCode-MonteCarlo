#include "SIBusAdapter.h"

using namespace std;
using namespace core;
//using namespace solve;

//const char* SIBusAdapter::SEGMENT_NAME = "SIBusSharedSegment";
//const int SIBusAdapter::SEGMENT_SIZE = 65535;
const char* SIBusAdapter::IPC_NAME_TO_ADAPTER = "SIBusShared_toAdapter";
const char* SIBusAdapter::IPC_NAME_FROM_ADAPTER = "SIBusShared_fromAdapter";
const int SIBusAdapter::MAX_MESSAGES = 40000;
const int SIBusAdapter::MESSAGE_SIZE = 200;

// Constructors/Destructors
//  

SIBusAdapter::SIBusAdapter ( ) : input(NULL),
				 output(NULL),
				 state(DATA),
				 displayWarnings(true),
				 displayReceivedLines(true),
				 disableThreadReceptionSubroutine(false) {
  boost::interprocess::message_queue::remove(IPC_NAME_TO_ADAPTER);
  boost::interprocess::message_queue::remove(IPC_NAME_FROM_ADAPTER);
  input = new boost::interprocess::message_queue(
	        boost::interprocess::open_or_create,
		IPC_NAME_TO_ADAPTER,
		MAX_MESSAGES,
		MESSAGE_SIZE);
  output = new boost::interprocess::message_queue(
	        boost::interprocess::open_or_create,
		IPC_NAME_FROM_ADAPTER,
		MAX_MESSAGES,
		MESSAGE_SIZE);

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

/*
std::istream& SIBusAdapter::getInput() {
  return input;
}

std::ostream& SIBusAdapter::getOutput() {
  return output;
}
*/

boost::interprocess::message_queue* SIBusAdapter::getInput() {
  return input;
}

boost::interprocess::message_queue* SIBusAdapter::getOutput() {
  return output;
}

void SIBusAdapter::setDisplayWarnings(bool displayWarnings) {
  this->displayWarnings = displayWarnings;
}

void SIBusAdapter::setDisplayReceivedLines(bool displayLines) {
  this->displayReceivedLines = displayLines;
}

void SIBusAdapter::setDisableThreadReceptionSubroutine(bool disable) {
  this->disableThreadReceptionSubroutine = disable;
}

AdapterState SIBusAdapter::getState() {
  return state;
}

//  
// dealWithInput methods
//  

void SIBusAdapter::dealWithInput(string line) {
  if (line.empty())
    line = receptionSubroutine();
 
  if (displayReceivedLines)
    //cout << "Received line: "  << line;

  try {
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
  } catch (AdapterException& e) {
    cout << "AdapterException:" << e.what() << endl;
  }
}

void SIBusAdapter::dealWithInputData(string line) {
  vector<string> tokens = tokenize(line, " ");
  if (line.find("VAR_BINDER") != string::npos) {
    // VAR_BINDER = var(quant,type,name,domain)
    // verify that we have the right number of tokens
    if (tokens.size() == 3) {
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
    } else {
      printWarning("Warning: malformated input: ", line);
    }
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
  } else if (line.find("CLOSE_MODELING") != string::npos) {
    state = SEARCH;
    cout << "Setting state to SEARCH" << endl;
  } else {
    printWarning("Warning: Unrecognized data input: ", line);
  }
}

void SIBusAdapter::dealWithInputSearch(string line) {//TODO
  if (line == "CHOICE") {

  } else if (line == "FAIL") {

  } else if (line == "SUCCESS") {

  } else {

  }
}

//
// Variable construction
//

Quantifier SIBusAdapter::identifyQuantifier(string s_quant) {
  if (s_quant == "E") {
    return EXISTS;
  } else if (s_quant == "F") {
    return FORALL;
  } else {
    throw AdapterException("Error: Unrecognised quantifier: ", s_quant);
  }
}

Type SIBusAdapter::identifyType(string s_type) {
  if (s_type == "I") {
    return INTEGER;
  } else if (s_type == "B") {
    return BOOLEAN;
  } else {
    throw AdapterException("Error: Unrecognized type: ", s_type);
  }
}

Domain* SIBusAdapter::identifyDomain(string s_domain) {
  GET_VALUE(s_domain, s_value); // string s_value
  vector<string> bound = tokenize(s_value, ":");
  if (bound.size() != 2) {
    throw AdapterException("Error: malformated domain: ", s_domain);
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

//
// Constraint construction
//

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
    throw AdapterException("Error: Unrecognised constraint type: ", type);
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
    throw AdapterException("Error: Unrecognised comparison type: ", type);
  }
}

ConstraintArgument* SIBusAdapter::identifyConstraintArgument(string argument) {
  GET_VALUE(argument, s_value) // string s_value
  if (argument.find("var") != string::npos) {
    Variable* variable = problem->getVariable(s_value);
    if (variable != NULL) {
      return variable;
    } else {
      throw AdapterException("Error: unknown variable in constraint argument: ", s_value);
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


//
// Thread handling
//

void SIBusAdapter::run() {
  while (state != EXIT) {
    string line;
    // reception subroutines should be disable in unit tests
    if (!disableThreadReceptionSubroutine)
      line = receptionSubroutine();
    mutex.lock();
    //manage event
    if (!disableThreadReceptionSubroutine) // same as above
      dealWithInput(line);

    mutex.unlock();
    if (disableThreadReceptionSubroutine) // ditto
      event.wait();
  }
  mutex.unlock();
}

//
// Communicate with SIBus
//

std::string SIBusAdapter::receptionSubroutine() {
  string line;
  line.resize(MESSAGE_SIZE);
  unsigned int receivedSize;
  unsigned int priority;
  input->receive(&line[0], MESSAGE_SIZE, receivedSize, priority);
  return line;
}

void SIBusAdapter::sendSolution(Solution* solution) {
  std::string outputString("SOLUTION         = ");
  // Transmit variables & their associated values
  for (pair<Variable*, Value*> currentPair : solution->getValues()) {
    outputString.append(" val(").append(currentPair.first->getName()).append(",");
    outputString.append(currentPair.second->getValueAsString()).append(")");
  }
  // Transmit additional information?
  
  // End of transmission
  //output << endl;
  output->send(outputString.data(), outputString.size(), 0);
}

//review that!!!
void SIBusAdapter::sendSwapAsk(Variable* var, const core::Value& val1, const core::Value& val2) {
  std::string outputString("SWAP_ASK         =");
  outputString.append(" idVar(").append(var->getName()).append(")");
  //outputString.append(" idVal(").append(val1.getValueAsString()).append(")");
  //outputString.append(" idVal(").append(val2.getValueAsString()).append(")");
  //output << endl;
  output->send(outputString.data(), outputString.size(), 0);
}

void SIBusAdapter::sendDomain(Variable* var, std::vector<std::pair<int, int> >& values) {
  std::string outputString("DOMAIN           =");
  outputString.append(" idVar(").append(var->getName()).append(")");
  for (std::pair<int, int> value : values) {
    outputString.append(" ").append(to_string(value.first));
  }
  cout << "Sending line: " << outputString << endl;;
  output->send(outputString.data(), outputString.size(), 0);
}

//
// Utility methods
//

void SIBusAdapter::printWarning(std::string message) {
  if (displayWarnings)
    cerr << message << endl;
}

void SIBusAdapter::printWarning(std::string message, std::string line) {
  if (displayWarnings)
    cerr << message << line << endl;
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
