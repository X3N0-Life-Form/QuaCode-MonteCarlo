#include "BooleanVariable.h"

using namespace core;

// Constructors/Destructors
//  

BooleanVariable::BooleanVariable ( ) {
}

BooleanVariable::BooleanVariable(Quantifier quant, Type type, std::string name, Domain* domain)
  : Variable(quant, type, name, domain) {

}

BooleanVariable::~BooleanVariable ( ) { }

//  
// Methods
//  

Type BooleanVariable::getType() {
  return BOOLEAN;
}

// Accessor methods
//  


// Other methods
//  


