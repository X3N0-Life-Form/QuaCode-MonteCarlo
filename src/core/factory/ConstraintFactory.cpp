#include "ConstraintFactory.h"

using namespace core;

Constraint* ConstraintFactory::createConstraint(constraint_type constraintType, comparison_type comparisonType) {
  //TODO: recognise boolean constraints
  return new IntegerConstraint(constraintType, comparisonType);
}
