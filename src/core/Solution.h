#ifndef SOLUTION_H
#define SOLUTION_H

#include "../solve/Validator.h"
#include "Variable.h"
#include "Value.h"

using namespace core;
using namespace solve;


class Solution {

private:
	std::vector<std::pair<Variable *, Value *> > values;
	Validator * validator;
	std::vector<std::pair<Variable *, int> > cfl;

public:	

  Solution ();

  std::vector<std::pair<Variable *, Value *> > getValues();

  std::vector<std::pair<Variable *, int> >  getCfl();

  void addValue(Variable* var, Value* val);

  void modifValue(int index, Value* val);

  void generateValueVector();

  // set all variables
  void generateCflVector();
  // set all values to 0
  void initCfl();

  // update cfl and return nb of conflicts
  int updateCfl();

  //used into updateCfl()
  void incrementCfl(ConstraintArgument * arg);

  // return var index (var with the smallest cfl)
    // must return the index of values
  int choice();


};

#endif