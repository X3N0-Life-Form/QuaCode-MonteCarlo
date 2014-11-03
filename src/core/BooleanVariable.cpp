#include "BooleanVariable.h"

using namespace core;

// Constructors/Destructors
//  

BooleanVariable::BooleanVariable ( ) {
}

BooleanVariable::BooleanVariable(Quantifier quant, Type type, std::string name, Domain* domain) : Variable(quant, type, name, domain)
   {
   	bDomain = new Domain(0,1);
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


