
#ifndef BOOLEANVARIABLE_H
#define BOOLEANVARIABLE_H
#include "Variable.h"

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


  /**
   * Empty Constructor
   */
  BooleanVariable ( );

  /**
   * Regular Constructor
   */
  BooleanVariable(Quantifier quant, Type type, std::string name, Domain* domain);

  /**
   * Empty Destructor
   */
  virtual ~BooleanVariable ( );

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

#endif // BOOLEANVARIABLE_H
