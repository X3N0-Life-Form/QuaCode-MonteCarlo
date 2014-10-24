
#ifndef INTEGERCONSTRAINT_H
#define INTEGERCONSTRAINT_H
#include "Constraint.h"

#include <string>
#include <vector>



namespace core {


/**
  * class IntegerConstraint
  * 
  */

class IntegerConstraint : public Constraint
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  IntegerConstraint (constraint_type cstT, comparison_type cmpT );

  virtual ~IntegerConstraint ( );

  virtual Type getType();

};
}; // end of package namespace

#endif // INTEGERCONSTRAINT_H
