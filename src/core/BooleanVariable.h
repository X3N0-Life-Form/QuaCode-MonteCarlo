
#ifndef BOOLEANVARIABLE_H
#define BOOLEANVARIABLE_H
#include "Variable.h"
#include "Domain.h"

#include <string>

namespace core {


/**
  * class BooleanVariable
  * 
  */

class BooleanVariable : public Variable
{
public:

  // Constructors/Destructors
  //  
  BooleanVariable();
  BooleanVariable(Quantifier quant, Type type, std::string name, Domain* domain);
  virtual ~BooleanVariable ( );

  // Public Methods
  //
  virtual Type getType();

private:
  Domain* bDomain;

};
}; // end of package namespace

#endif // BOOLEANVARIABLE_H
