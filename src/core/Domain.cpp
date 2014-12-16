#include "Domain.h"
using namespace core;

// Constructors/Destructors
//  

Domain::Domain (int val1, int val2) : type(INTEGER) {
	firstValue = val1;
	lastValue = val2;
	sizeAlreadyChecked = 0;
	alreadyChecked = new int[(val2 - val1 + 1)];
  size = val2 - val1 + 1;
  generateCflVector();
}

std::vector<std::pair<int, int> >  Domain::getCfl(){
  return cfl;
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

  int Domain::getSize() {
    return size;
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

void Domain::generateCflVector(){
  for (unsigned int i = firstValue; i <= lastValue; i++) {
    cfl.push_back(std::pair<int, int>(i, 0));
  }
}

 void Domain::initCfl() {
  for (unsigned int i = 0; i < cfl.size();i++){
    cfl[i].second = 0;
  }
 }

  void Domain::incrementCfl(int value) {
    for (unsigned int i = 0; i < cfl.size(); i++) {
      if (cfl[i].first == value){
        cfl[i].second++;
        break;
      }
    }
 }
// attention : si value = 9,alors cfl[9-1].second = c !!!
 void Domain::setCflForValue(int value, int c){
    for (int i = 0; i < cfl.size(); i++) {
      if (cfl[i].first == value) {
        cfl[i].second = c;
        break;
      }
    }
 }


 // total of cfl for each possible value
 int Domain::totalCfl() {
  int sum = 0;
  for (int i = 0; i < cfl.size(); i++) {
      sum += cfl[i].second;
  }
  return sum;
}

// Operators
//

bool Domain::operator==(ConstraintArgument& right) {
  Domain& dom = dynamic_cast<Domain&>(right);
  return getType() == dom.getType()
    && getFirstValue() == dom.getFirstValue()
    && getLastValue() == dom.getLastValue();
}
