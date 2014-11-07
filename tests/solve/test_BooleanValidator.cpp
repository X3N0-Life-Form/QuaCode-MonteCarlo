#include "test_BooleanValidator.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_BooleanValidator);

void Test_BooleanValidator::setUp() {
  prob = new Problem();
  validator = new BooleanValidator(prob);
}

void Test_BooleanValidator::tearDown() {
  if (validator != NULL) {
    delete(validator);
  }
}

void Test_BooleanValidator::test_validateConstraint() {

	Domain* boolDomain = new Domain(0,1);
 	Variable* varBOOL1 = VariableFactory::createVariable(EXISTS, BOOLEAN, "x1", boolDomain);
 	Variable* varBOOL2 = VariableFactory::createVariable(EXISTS, BOOLEAN, "x2", boolDomain);
 	Variable* varBOOL3 = VariableFactory::createVariable(EXISTS, BOOLEAN, "x3", boolDomain);
 	Variable* varBOOL4 = VariableFactory::createVariable(EXISTS, BOOLEAN, "x4", boolDomain);
 	Value* vTrue = new Value(true);
	Value* vFalse= new Value(false);	

	pair<Variable *, Value *> p;
	//AND , EQ
	//test : true and true = true
		vector<pair<Variable *, Value *> > solution1;
		solution1.reserve(3);
		
		p.first = varBOOL1;
		p.second = vTrue;
		solution1.push_back(p);
		p.first = varBOOL2;
		p.second = vTrue;
		solution1.push_back(p);
		p.first = varBOOL3;
		p.second = vTrue;
		solution1.push_back(p);

		Constraint* BoolConstraint1 = new BooleanConstraint(AND,EQ);
		BoolConstraint1->addArgument(varBOOL1);
		BoolConstraint1->addArgument(varBOOL2);
		BoolConstraint1->addArgument(varBOOL3);
		
		CPPUNIT_ASSERT_EQUAL(true,validator->validateConstraint(BoolConstraint1, solution1));

	//OR , EQ
	//test : true or false = true
		vector<pair<Variable *, Value *> > solution2;
		solution2.reserve(3);

		p.first = varBOOL1;
		p.second = vTrue;
		solution2.push_back(p);
		p.first = varBOOL2;
		p.second = vFalse;
		solution2.push_back(p);
		p.first = varBOOL3;
		p.second = vTrue;
		solution2.push_back(p);

		Constraint* BoolConstraint2 = new BooleanConstraint(OR,EQ);
		BoolConstraint2->addArgument(varBOOL1);
		BoolConstraint2->addArgument(varBOOL2);
		BoolConstraint2->addArgument(varBOOL3);
		
		CPPUNIT_ASSERT_EQUAL(true,validator->validateConstraint(BoolConstraint2, solution2));

	//XOR , EQ
	//test : true xor true = false
		vector<pair<Variable *, Value *> > solution3;
		solution3.reserve(3);

		p.first = varBOOL1;
		p.second = vTrue;
		solution3.push_back(p);
		p.first = varBOOL2;
		p.second = vTrue;
		solution3.push_back(p);
		p.first = varBOOL3;
		p.second = vFalse;
		solution3.push_back(p);

		Constraint* BoolConstraint3 = new BooleanConstraint(XOR,EQ);
		BoolConstraint3->addArgument(varBOOL1);
		BoolConstraint3->addArgument(varBOOL2);
		BoolConstraint3->addArgument(varBOOL3);
	
		CPPUNIT_ASSERT_EQUAL(true,validator->validateConstraint(BoolConstraint3, solution3));

	//IMP , EQ
	//test : false IMP true != false
		vector<pair<Variable *, Value *> > solution4;
		solution4.reserve(3);

		p.first = varBOOL1;
		p.second = vFalse;
		solution4.push_back(p);
		p.first = varBOOL2;
		p.second = vTrue;
		solution4.push_back(p);
		p.first = varBOOL3;
		p.second = vFalse;
		solution4.push_back(p);

		Constraint* BoolConstraint4 = new BooleanConstraint(IMP,EQ);
		BoolConstraint4->addArgument(varBOOL1);
		BoolConstraint4->addArgument(varBOOL2);
		BoolConstraint4->addArgument(varBOOL3);
	
		CPPUNIT_ASSERT_EQUAL(false,validator->validateConstraint(BoolConstraint4, solution4));
}

