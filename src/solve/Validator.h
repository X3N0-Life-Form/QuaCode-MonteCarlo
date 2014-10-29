
#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "../core/Problem.h"
#include "../core/Constant.h"

#include <string>
#include <vector>


using namespace core;

namespace solve {


/**
  * class Validator
  * 
  */

class Validator
{

private:
  Problem * prob;

public:

  // Constructors/Destructors

  Validator (Problem * pb);

  virtual ~Validator ( );

  virtual bool validateConstraint(Constraint * cst, std::vector<std::pair<Variable *, Value *> > values) = 0;

protected:
  static int getArgumentIValue(ConstraintArgument* argument, std::vector<std::pair<Variable *, Value *> > values);
  static bool getArgumentBValue(ConstraintArgument* argument, std::vector<std::pair<Variable *, Value *> > values);
  static Value* getVariableValue(Variable* var, std::vector<std::pair<Variable *, Value *> > values);
  static bool checkComparison(int value, comparison_type CT, int lastValue);


};
}; // end of package namespace

#endif // VALIDATOR_H
