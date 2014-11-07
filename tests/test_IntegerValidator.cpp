#include "test_IntegerValidator.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_IntegerValidator);

void Test_IntegerValidator::setUp() {
  prob = new Problem();
  validator = new IntegerValidator(prob);
}

void Test_IntegerValidator::tearDown() {
  if (validator != NULL) {
    delete(validator);
  }
}

void Test_IntegerValidator::test_validateConstraint() {

	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", new Domain(3,3));
	Variable* varINT2 = VariableFactory::createVariable(EXISTS, INTEGER, "x2", new Domain(3,3));
	Variable* varINT3 = VariableFactory::createVariable(EXISTS, INTEGER, "x3", new Domain(4,4));
	Variable* varINT4 = VariableFactory::createVariable(EXISTS, INTEGER, "x4", new Domain(10,10));
	Variable* varINT5 = VariableFactory::createVariable(EXISTS, INTEGER, "x5", new Domain(20,20));
	Variable* varINT6 = VariableFactory::createVariable(EXISTS, INTEGER, "x6", new Domain(100,100));

	Value* vINT1 = new Value(3);
	Value* vINT2 = new Value(3);
	Value* vINT3 = new Value(4);
	Value* vINT4 = new Value(10);
	Value* vINT5 = new Value(20);
	Value* vINT6 = new Value(100);

	//Linear , EQ
	//test : 10*4 + 20*3 = 100
		vector<pair<Variable *, Value *> > solution1;
		solution1.reserve(5);

		pair<Variable *, Value *> p;
		p.first = varINT2;
		p.second = vINT2;
		solution1.push_back(p);
		p.first = varINT3;
		p.second = vINT3;
		solution1.push_back(p);
		p.first = varINT4;
		p.second = vINT4;
		solution1.push_back(p);
		p.first = varINT5;
		p.second = vINT5;
		solution1.push_back(p);
		p.first = varINT6;
		p.second = vINT6;
		solution1.push_back(p);
		
		
		Constraint* IntConstraint1 = new IntegerConstraint(LINEAR,EQ);
		IntConstraint1->addArgument(varINT3);
		IntConstraint1->addArgument(varINT4);
		IntConstraint1->addArgument(varINT2);
		IntConstraint1->addArgument(varINT5);
		IntConstraint1->addArgument(varINT6);
		CPPUNIT_ASSERT_EQUAL(true,validator->validateConstraint(IntConstraint1, solution1));

	//TIMES , GR
	//test : 3 * 4 > 10
		vector<pair<Variable *, Value *> > solution2;
		solution2.reserve(3);

		p.first = varINT2;
		p.second = vINT2;
		solution2.push_back(p);
		p.first = varINT3;
		p.second = vINT3;
		solution2.push_back(p);
		p.first = varINT4;
		p.second = vINT4;
		solution2.push_back(p);

		Constraint* IntConstraint2 = new IntegerConstraint(TIMES,GR);
		IntConstraint2->addArgument(varINT2);
		IntConstraint2->addArgument(varINT3);
		IntConstraint2->addArgument(varINT4);
		CPPUNIT_ASSERT_EQUAL(true,validator->validateConstraint(IntConstraint2, solution2));

	//C_EQ 
	//test : 3 = 3 != 4
		vector<pair<Variable *, Value *> > solution3;
		solution3.reserve(3);

		p.first = varINT1;
		p.second = vINT1;
		solution3.push_back(p);
		p.first = varINT2;
		p.second = vINT2;
		solution3.push_back(p);

		Constraint* IntConstraint3 = new IntegerConstraint(C_EQ,EQ);
		IntConstraint3->addArgument(varINT1);
		IntConstraint3->addArgument(varINT2);	
		CPPUNIT_ASSERT_EQUAL(true,validator->validateConstraint(IntConstraint3, solution3));

		p.first = varINT3;
		p.second = vINT3;
		solution3.push_back(p);
		IntConstraint3->addArgument(varINT3);
		CPPUNIT_ASSERT_EQUAL(false,validator->validateConstraint(IntConstraint3, solution3));
}

