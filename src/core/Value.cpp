#include "Value.h"

using namespace std;
using namespace core;

// Constructors/Destructors
//  

Value::Value(int value) : iValue(value), varType(INTEGER) {
}

Value::Value(bool value) : bValue(value), varType(BOOLEAN) {
}

Value::~Value ( ) { }

// Accessor methods
//  

Type Value::getVarType() {
  return varType;
}

bool Value::getBValue(){
  return bValue;
}

int Value::getiValue(){
  return iValue;
}

string Value::getValueAsString() const {
  switch (varType) {
  case INTEGER:
    return std::to_string(iValue);
  case BOOLEAN:
    if (bValue)
      return "1";
    else
      return "0";
  default:
    return "Error";
  }
}

bool Value::operator==(Value& right) {
  return varType == right.varType
    && (iValue == right.iValue || bValue == right.bValue);
}
