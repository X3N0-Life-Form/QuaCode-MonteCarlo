#include "Variable.h"

using namespace core;

// Constructors/Destructors
//  

Variable::Variable ( ) {
}

Variable::Variable(Quantifier quant, Type type, std::string name, Domain* domain) 
  : quantifier(quant), type(type), name(name), domain(domain) {
}

string Variable::getName() {
  return name;
}

Domain* Variable::getDomain() {
  return domain;
}

Quantifier Variable::getQuantifier() {
  return quantifier;
}

Variable::~Variable ( ) { }

bool Variable::operator==(ConstraintArgument& right) {
  Variable& var = dynamic_cast<Variable&>(right);
  return name == var.name
    && type == var.type
    && quantifier == var.quantifier
    && *domain == *var.domain;
}

void Variable::setId(unsigned int id) {
	this->id;
}

unsigned int Variable::getId() {
	return id;
}

