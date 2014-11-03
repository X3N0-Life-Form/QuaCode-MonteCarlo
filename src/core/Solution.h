#ifndef SOLUTION_H
#define SOLUTION_H

#include "Problem.h"
#include "Variable.h"
#include "Value.h"

using namespace core;


class Solution {

private:
	std::vector<std::pair<Variable *, Value *> > values;
	Problem * problem;

public:	

  Solution ();

  std::vector<std::pair<Variable *, Value *> > getValues();

  void addValue(Variable* var, Value* val);

  void generateValueVector();


};

#endif