#ifndef CONSTANT_H
#define CONSTANT_H

#include "Value.h"
#include "../Type.h"
#include "ConstraintArgument.h"

namespace core {
  class Constant : public ConstraintArgument {
  private:
    Value* value;

  public:
    Constant(Value* value);
    Type getType();
    Value* getValue();

    virtual bool operator==(ConstraintArgument& right);
  };
};

#endif
