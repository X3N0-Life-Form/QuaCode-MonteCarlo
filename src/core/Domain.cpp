#include "Domain.h"
#include <iostream>

using namespace core;
using namespace std;
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
  for (int i = firstValue; i <= lastValue; i++) {
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

void Domain::replace(std::vector<std::pair<int, int> > vect) {
  for(int i = 0; i < vect.size(); i++) {
    cfl[i].first = vect[i].first;
    cfl[i].second = vect[i].second;
  }
}

/*
procédure tri_insertion(tableau T, entier n)
      pour i de 1 à n-1
          x ← T[i]
          j ← i
          tant que j > 0 et T[j - 1] > x
              T[j] ← T[j - 1]
              j ← j - 1
          fin tant que
          T[j] ← x
     fin pour
  fin procédure 

*/



std::vector<std::pair<int, int> > Domain::sortedCfl() {
  std::vector<std::pair<int, int> > toReturn;
  
  for (int i = firstValue; i <= lastValue; i++) {
    toReturn.push_back(std::pair<int, int>(i, 0));
  }

  //copy values of cfl into toReturn
  for (unsigned int i = 0; i < cfl.size(); i++) {
    toReturn[i].first = cfl[i].first;
    toReturn[i].second = cfl[i].second;
  }

  // sort toReturn => min cfl value first
  //test if associated values are the same (for example (5,3)) and if it is sorted from min cfl value (the second one) to max cfl value
  for (unsigned int i = 0; i < cfl.size(); i++) {
      int xfirst = toReturn[i].first;
      int xsecond = toReturn[i].second;
      int j = i;
      while(j > 0 && toReturn[j - 1].second > xsecond) {
        toReturn[j].first = toReturn[j - 1].first;
        toReturn[j].second = toReturn[j-1].second;
        j--;
      }
      toReturn[j].second = xsecond;
      toReturn[j].first = xfirst;
  }
  return toReturn;
}

// Operators

bool Domain::operator==(ConstraintArgument& right) {
  Domain& dom = dynamic_cast<Domain&>(right);
  return getType() == dom.getType()
    && getFirstValue() == dom.getFirstValue()
    && getLastValue() == dom.getLastValue();
}
