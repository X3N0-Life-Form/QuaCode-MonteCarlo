#include "Constant.h"

using namespace core;
using namespace std;

Constant::Constant(Value* value) : value(value) {
}

Type Constant::getType() {
  return value->getVarType();
}

Value* Constant::getValue() {
  return value;
}

bool Constant::operator==(ConstraintArgument& right) {
  Constant& constant = dynamic_cast<Constant&>(right);
  return getType() == constant.getType()
    && *value == *constant.value;
}
