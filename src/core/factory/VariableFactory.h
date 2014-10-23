#ifndef VARIABLEFACTORY_H
#define VARIABLEFACTORY_H

#include <string>

#include "../Variable.h"
#include "../BooleanVariable.h"
#include "../IntegerVariable.h"

namespace core {
  class VariableFactory {

    // Public Static Methods
    //
  public:
    static Variable* createVariable(Quantifier quant, Type type, std::string name, Domain* domain);
    
  };
};

#endif
