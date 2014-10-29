
#ifndef BOOLEANVALIDATOR_H
#define BOOLEANVALIDATOR_H
#include "Validator.h"

#include <string>
#include <vector>



namespace solve {


/**
  * class BooleanValidator
  * 
  */

class BooleanValidator : public Validator
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  BooleanValidator (Problem * pb);

  /**
   * Empty Destructor
   */
  virtual ~BooleanValidator ( );

  virtual bool validateConstraint(Constraint * cst, std::vector<std::pair<Variable *, Value *> > values);

  

};
}; // end of package namespace

#endif // BOOLEANVALIDATOR_H
