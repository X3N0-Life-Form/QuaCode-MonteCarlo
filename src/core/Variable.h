
#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Type.h"
#include "Domain.h"
#include "Quantifier.h"

#include <string>
#include <vector>



namespace core {


/**
  * class Variable
  * 
  */

class Variable
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Variable ( );

  /**
   * Regular Constructor
   */
  Variable(Quantifier quant, Type type, std::string name, Domain* domain);
  
  /**
   * Empty Destructor
   */
  virtual ~Variable ( );

  // Public Methods
  //

  /**
   * @return Type
   */
  virtual Type getType ( ) = 0;


private:

  // Static Private attributes
  //  

  // Private attributes
  //  
  std::string name;
  Domain* domain;
  Quantifier quantifier;
  Type type;
  
public:


  // Private attribute accessor methods
  //  



};
}; // end of package namespace

#endif // VARIABLE_H
