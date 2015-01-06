#include "VariableFactory.h"

using namespace core;

unsigned int VariableFactory::numberOfVars = 0;

Variable* VariableFactory::createVariable(Quantifier quant, Type type, std::string name, Domain* domain) {
  Variable* var = NULL;
  switch (type) {
  case INTEGER:
    var = new IntegerVariable(quant, type, name, domain);
    break;
  case BOOLEAN:
    var = new BooleanVariable(quant, type, name, new Domain(0,1));
    break;
  }
  
  var->setId(numberOfVars);
  numberOfVars++;
  return var;
}
