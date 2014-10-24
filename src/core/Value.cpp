#include "Value.h"

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


