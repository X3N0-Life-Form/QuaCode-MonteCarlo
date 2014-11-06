
#ifndef BOOLEANCONSTRAINT_H
#define BOOLEANCONSTRAINT_H
#include "Constraint.h"

#include <string>
#include <vector>



namespace core {


/**
  * class BooleanConstraint
  * 
  */

class BooleanConstraint : public Constraint
{
public:

  // Constructors/Destructors
  //  

  BooleanConstraint (constraint_type cstT, comparison_type cmpT );


  virtual ~BooleanConstraint ( );

  virtual Type getType();


};
}; // end of package namespace

#endif // BOOLEANCONSTRAINT_H
