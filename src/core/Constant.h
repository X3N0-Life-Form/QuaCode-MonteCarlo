#ifndef CONSTANT_H
#define CONSTANT_H

#include "Value.h"
#include "../Type.h"
#include "ConstraintArgument.h"

namespace core {
  class Constant : ConstraintArgument {
  private:
    Value value;

  public:
    Constant(Value value);
    Type getType();
  };
};

#endif
