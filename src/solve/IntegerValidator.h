
#ifndef INTEGERVALIDATOR_H
#define INTEGERVALIDATOR_H
#include "Validator.h"

#include <string>
#include <vector>


namespace solve {


/**
  * class IntegerValidator
  * 
  */
class IntegerValidator : public Validator
{
public:

  // Constructors/Destructors
  IntegerValidator (Problem * pb);
  virtual ~IntegerValidator ( );

  virtual bool validateConstraint(Constraint * cst, std::vector<std::pair<Variable *, Value *> > values);
};
}; // end of package namespace

#endif // INTEGERVALIDATOR_H
