
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <string>
#include <vector>

#include "../Type.h"
#include "Variable.h"
#include "ConstraintArgument.h"


namespace core {

enum comparison_type {
  NQ,
  EQ,
  LQ,
  LE,
  GQ,
  GR
};

enum constraint_type {
  AND,
  OR,
  XOR,
  IMP,
  C_EQ, //same as EQ, just to avoid conflicts with previous declaration
  TIMES,
  LINEAR,
  RE_AND,
  RE_OR,
  RE_IMP,
  RE_XOR,
  RE_EQ,
  RE_TIMES,
  RE_LINEAR,
  ELEMENT
};

/**
  * class Constraint
  * 
  */

class Constraint
{

private:
  std::vector<ConstraintArgument *> arguments;
  constraint_type constraintType;
  comparison_type comparisonType;

public:

  // Constructors/Destructors
  //  

  Constraint (constraint_type cstT, comparison_type cmpT);

  virtual ~Constraint ( );

  //getters

  constraint_type getConstraintType ();
  comparison_type getComparisonType();
  std::vector<ConstraintArgument * > getArguments();

  void addArgument(ConstraintArgument * var);


  /**
   * @return Type
   */
  virtual Type getType ( ) = 0;

};
}; // end of package namespace

#endif // CONSTRAINT_H
