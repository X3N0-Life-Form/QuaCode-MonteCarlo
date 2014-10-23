#include "IntegerVariable.h"

using namespace core;

// Constructors/Destructors
//  

IntegerVariable::IntegerVariable ( ) {
}

IntegerVariable::IntegerVariable(Quantifier quant, Type type, std::string name, Domain* domain)
  : Variable(quant, type, name, domain) {

}

IntegerVariable::~IntegerVariable ( ) { }

//  
// Methods
//  

Type IntegerVariable::getType() {
  return INTEGER;
}

// Accessor methods
//  


// Other methods
//  


