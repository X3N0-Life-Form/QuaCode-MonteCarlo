#ifndef VARIABLEFACTORY_H
#define VARIABLEFACTORY_H

#include <string>

#include "../Variable.h"
#include "../BooleanVariable.h"
#include "../IntegerVariable.h"

namespace core {
  class VariableFactory {

  private:
    static unsigned int numberOfVars;

  public:
    /**
     * Note: A variable with no domain (= NULL) is an auxilliary variable.
     */
    static Variable* createVariable(Quantifier quant, Type type, std::string name, Domain* domain = NULL);
    
  };
};

#endif
