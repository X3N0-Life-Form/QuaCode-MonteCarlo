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

public:	

  Solution ();

  std::vector<std::pair<Variable *, Value *> > getValues();

  void addValue(Variable* var, Value* val);

  void generateValueVector();


};

#endif