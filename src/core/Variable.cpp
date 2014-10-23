#include "Variable.h"

using namespace core;

// Constructors/Destructors
//  

Variable::Variable ( ) {
}

Variable::Variable(Quantifier quant, Type type, std::string name, Domain* domain) 
  : quantifier(quant), type(type), name(name), domain(domain) {
}

Variable::~Variable ( ) { }

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


