#ifndef CONSTRAINTARGUMENT_H
#define CONSTRAINTARGUMENT_H

#include "../Type.h"

namespace core {
  class ConstraintArgument {
  public:
    virtual Type getType() = 0;
  };
};

#endif
