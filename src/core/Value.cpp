#include "Value.h"

using namespace core;

// Constructors/Destructors
//  

Value::Value ( ) {
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


