#include "test_Problem.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Problem);

void Test_Problem::setUp() {
  prob = new Problem();
}

void Test_Problem::tearDown() {
  if (prob != NULL) {
    delete(prob);
  }
}

void Test_Problem::test_addANDgetVariable(){
	Domain* myDomain = new Domain(1,40);
	Domain* TargetDomain1 = new Domain(21,25);
	Domain* TargetDomain2 = new Domain(29,30);
	Domain* TargetDomain3 = new Domain(390,400);

	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain);
	Variable* varINT2 = VariableFactory::createVariable(EXISTS, INTEGER, "x2", myDomain);
	Variable* varINT3 = VariableFactory::createVariable(FORALL, INTEGER, "x3", TargetDomain1);
	Variable* varINT4 = VariableFactory::createVariable(FORALL, INTEGER, "x4", TargetDomain2);
	Variable* varINT5 = VariableFactory::createVariable(FORALL, INTEGER, "x5", TargetDomain3);

	Variable* varBOOL = VariableFactory::createVariable(EXISTS, BOOLEAN, "b1", myDomain);

	prob->addVariable(varINT1);
	prob->addVariable(varINT2);
	prob->addVariable(varINT3);
	prob->addVariable(varINT4);
	prob->addVariable(varINT5);
	prob->addVariable(varBOOL);

	CPPUNIT_ASSERT(prob->getVariables().size()==6);
	CPPUNIT_ASSERT_EQUAL(varINT1,prob->getVariable("x1"));
	CPPUNIT_ASSERT(varINT5!=prob->getVariable("x4"));
	CPPUNIT_ASSERT(prob->getVariable("b1")!=NULL);
}
void Test_Problem::test_addANDgetConstraint(){
	Constraint* IntConstraint = new IntegerConstraint(LINEAR,LQ);
	Constraint* BoolConstraint = new BooleanConstraint(OR,LQ);
	prob->addConstraint(IntConstraint);
	prob->addConstraint(BoolConstraint);
	CPPUNIT_ASSERT(prob->getConstraints().size()==2);
}

void Test_Problem::test_getDomain(){
	Domain* myDomain = new Domain(1,40);
	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain);
	prob->addVariable(varINT1);
	CPPUNIT_ASSERT_EQUAL(myDomain,prob->getDomain(1,40));
  }
