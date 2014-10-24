#ifndef CONSTRAINTFACTORY_H
#define CONSTRAINTFACTORY_H

#include "../Constraint.h"
#include "../BooleanConstraint.h"
#include "../IntegerConstraint.h"

namespace core {

  class ConstraintFactory {
  public:
    static Constraint* createConstraint(constraint_type constraintType, comparison_type comparisonType);
  };

};

#endif
