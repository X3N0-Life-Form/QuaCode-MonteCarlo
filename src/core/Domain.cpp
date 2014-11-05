#include "Domain.h"

using namespace core;

// Constructors/Destructors
//  

Domain::Domain (int val1, int val2) : type(INTEGER) {
	firstValue = val1;
	lastValue = val2;
	sizeAlreadyChecked = 0;
	alreadyChecked = new int[(val2 - val1 + 1)];

}

Domain::~Domain ( ) { 
	delete [] alreadyChecked;
}


// Accessor methods
//  
Type Domain::getType() {
  return type;
}

  int Domain::getFirstValue() {
  	return firstValue;
  }

  int Domain::getLastValue() {
  	return lastValue;
  }

  int * Domain::getAlreadyChecked() {
  	return alreadyChecked;
  }

  int Domain::getSizeAlreadyChecked() {
  	return sizeAlreadyChecked;
  }

  // return true if value added
  bool Domain::addValue(int value){
  	if (value >= firstValue && value <= lastValue && !alreadyInto(value)){
  		alreadyChecked[sizeAlreadyChecked] = value;
  		sizeAlreadyChecked++;
  		return true;
  	}
  	else {
  		return false;
  	}
  }

// used into addValue
// check if value already into alreadyChecked => if yes returns true.
bool Domain::alreadyInto(int value) {
  for (int i = 0; i < sizeAlreadyChecked; i++) {
    if (alreadyChecked[i] == value)
      return true;
  }
  return false;
}


// Operators
//

bool operator==(Domain& left, Domain& right) {
  return left.getType() == right.getType()
    && left.getFirstValue() == right.getFirstValue()
    && left.getLastValue() == right.getLastValue();
}
