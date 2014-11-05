#include "test_Validator.h"

#include "../src/solve/IntegerValidator.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Validator);

void Test_Validator::setUp() {
  prob = new Problem();
  validator = new IntegerValidator(prob);
}

void Test_Validator::tearDown() {
  if (validator != NULL) {
    delete(validator);
  }
}

void Test_Validator::test_getArgumentIValue() {
	vector<pair<Variable *, Value *> > solution;
 	solution.reserve(1);	
 	Domain* myDomain = new Domain(40,40);
 	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain);
 	Value* vINT1 = new Value(40);
 	pair<Variable *, Value *> p;
	p.first = varINT1;
	p.second = vINT1;
 	solution.push_back(p);
 	Constraint* IntConstraint = new IntegerConstraint(LINEAR,LQ);
	IntConstraint->addArgument(varINT1);
	vector<ConstraintArgument *> constraintArgs;
	constraintArgs = IntConstraint->getArguments();
	CPPUNIT_ASSERT_EQUAL(40,validator->getArgumentIValue(constraintArgs[0],solution));
}

void Test_Validator::test_getArgumentBValue() {
 	vector<pair<Variable *, Value *> > solution;
 	solution.reserve(1);	
 	Domain* myDomain = new Domain(1,1);
 	Variable* varBOOL = VariableFactory::createVariable(EXISTS, BOOLEAN, "x1", myDomain);
 	Value* vBOOL = new Value(true);
 	pair<Variable *, Value *> p;
	p.first = varBOOL;
	p.second = vBOOL;
 	solution.push_back(p);
 	Constraint* BoolConstraint = new BooleanConstraint(OR,LQ);
	BoolConstraint->addArgument(varBOOL);
	vector<ConstraintArgument *> constraintArgs;
	constraintArgs = BoolConstraint->getArguments();
	CPPUNIT_ASSERT_EQUAL(true,validator->getArgumentBValue(constraintArgs[0],solution));
}

void Test_Validator::test_getVariableValue() {
 	vector<pair<Variable *, Value *> > solution;
 	solution.reserve(1);	
 	Domain* myDomain = new Domain(40,40);
 	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain);
 	Value* vINT1 = new Value(40);
 	pair<Variable *, Value *> p;
	p.first = varINT1;
	p.second = vINT1;
 	solution.push_back(p);

 	CPPUNIT_ASSERT_EQUAL(40,validator->getVariableValue(varINT1,solution)->getiValue());
 	
}

void Test_Validator::test_checkComparison() {
 	
}

void Test_Validator::test_checkComparison_() {
 
}
