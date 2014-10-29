#include "SIBusAdapter.h"

using namespace std;
using namespace core;
//using namespace solve;

// Constructors/Destructors
//  

SIBusAdapter::SIBusAdapter ( ) : input(cin), output(cout), mode(DATA) {
  problem = new Problem();
}

SIBusAdapter::~SIBusAdapter ( ) { 
  delete(problem);
}

//  
// Methods
//  

void SIBusAdapter::dealWithInput() {
  string line;
  input >> line;
  switch (mode) {
  case DATA:
    dealWithInputData(line);
    break;
  case SEARCH:
    dealWithInputSearch(line);
    break;
  }
  
}

void SIBusAdapter::dealWithInputData(string line) {
  string word;
  input >> word;
  if (line == "VAR_BINDER") {
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
  int leftBracketPos = argument.find("(");
  int rightBracketPos = argument.find(")");
  string s_value = argument.substr(leftBracketPos + 1, rightBracketPos - 1);
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
    Domain* domain = problem->getDomain(lowerBoundary, upperBoundary);
    if (domain != NULL) {
      return domain;
    } else {
      cerr << "Constraint argument error: unknown domain " << s_value << endl;
      return NULL;
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
  return NULL;
}
constraint_type SIBusAdapter::identifyConstraintType(std::string type) {
  return AND;
}

comparison_type SIBusAdapter::identifyComparisonType(std::string type) {
  return NQ;
}

void SIBusAdapter::dealWithInputSearch(string line) {
  string word;
  input >> word;
  //TODO
}

//
// Other Functions
//

vector<string> tokenize(string toSplit, string token) {
  int pos;
  vector<string> result;
  while ((pos = toSplit.find(token)) != string::npos) {
    string nuString = toSplit.substr(0, pos - 1);
    result.push_back(nuString);
    toSplit = toSplit.substr(pos + 1);
  }
  return result;
}
