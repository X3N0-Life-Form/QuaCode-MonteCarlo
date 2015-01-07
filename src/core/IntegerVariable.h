
#ifndef INTEGERVARIABLE_H
#define INTEGERVARIABLE_H
#include "Variable.h"


#include <string>

namespace core {


/**
  * class IntegerVariable
  * 
  */

class IntegerVariable : public Variable
{
public:

  IntegerVariable ();
  IntegerVariable(Quantifier quant, Type type, std::string name, Domain* domain);
  virtual ~IntegerVariable ( );

  virtual Type getType();
};
}; // end of package namespace

#endif // INTEGERVARIABLE_H
