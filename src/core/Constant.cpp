#include "Constant.h"

using namespace core;
using namespace std;

Constant::Constant(Value value) : value(value) {
}

Type Constant::getType() {
  return value.getVarType();
}
