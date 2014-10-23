
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

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  IntegerVariable ( );

  /**
   * Regular Constructor
   */
  IntegerVariable(Quantifier quant, Type type, std::string name, Domain* domain);

  /**
   * Empty Destructor
   */
  virtual ~IntegerVariable ( );


  // Public Methods
  //

  virtual Type getType();

private:

  // Static Private attributes
  //  

  // Private attributes
  //  

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};
}; // end of package namespace

#endif // INTEGERVARIABLE_H
