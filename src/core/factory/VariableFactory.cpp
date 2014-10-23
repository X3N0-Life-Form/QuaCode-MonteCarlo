#include "VariableFactory.h"

using namespace core;

Variable* VariableFactory::createVariable(Quantifier quant, Type type, std::string name, Domain* domain) {
  switch (type) {
  case INTEGER:
    return new IntegerVariable(quant, type, name, domain);
  case BOOLEAN:
    return new BooleanVariable(quant, type, name, domain);
  }

  return NULL;
}
