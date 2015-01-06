#ifndef SOLUTION_H
#define SOLUTION_H

#include "../solve/Validator.h"
#include "Variable.h"
#include "Value.h"
#include "Problem.h"


using namespace solve;

namespace core {
class Solution {

private:
	std::vector<std::pair<Variable *, Value *> > values;
	Validator * validator;

public:	

  Solution (Validator * val);

  // TODO : constructeur par recopie

  std::vector<std::pair<Variable *, Value *> > getValues();

  //std::vector<std::pair<Variable *, int> >  getCfl();

  void addValue(Variable* var, Value* val);

  void modifValue(int index, Value* val);

  void generateValueVector();


  // update cfl and return nb of conflicts
  int updateCfl(Problem* problem);

    //used into updateCfl()
  void increment(ConstraintArgument * arg, Problem* problem);

    // return var index (var with the smallest cfl)
    // must return the index of values
  int choice();
/*



*/

};
}; // end of namespace core

#endif
