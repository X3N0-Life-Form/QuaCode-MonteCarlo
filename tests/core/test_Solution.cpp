#include "test_Solution.h"
#include "../../src/solve/IntegerValidator.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Solution);

void Test_Solution::setUp() {
	quantifier = EXISTS;
	type = INTEGER;
	name1 = "var1";
	name2 = "var2";
	domain = new Domain(1,10);
	intVar1 = new IntegerVariable(quantifier,type,name1,domain);
	domain = new Domain(15,20);
	intVar2 = new IntegerVariable(quantifier,type,name2,domain);
	prob = new Problem();
	prob->addVariable(intVar1);
	prob->addVariable(intVar2);
	cst=new IntegerConstraint(LINEAR,EQ);
	cst->addArgument(intVar1);
	cst->addArgument(intVar2);
	prob->addConstraint(cst);
	validator = new IntegerValidator(prob);
	solution = new Solution(validator);
	
}

void Test_Solution::tearDown() {
  if (solution != NULL) {
    delete(solution);
  }
}

void Test_Solution::test_getValues() {
	CPPUNIT_ASSERT_EQUAL(name1,solution->getValues()[0].first->getName());
}

void Test_Solution::test_addValue() {
	Value* v = new Value(5);
	solution->addValue(intVar1,v);
	CPPUNIT_ASSERT_EQUAL(5,solution->getValues()[0].second->getiValue());
}

void Test_Solution::test_modifValue() {
	Value* v = new Value(5);
	solution->modifValue(0,v);
	CPPUNIT_ASSERT_EQUAL(5,solution->getValues()[0].second->getiValue());
}

void Test_Solution::test_generateValueVector() {
	solution->generateValueVector();
	CPPUNIT_ASSERT(solution->getValues()[0].first!=NULL);	
}

void Test_Solution::test_updateCfl() {
	Value* v = new Value(3);
	solution->modifValue(0,v);	
	CPPUNIT_ASSERT_EQUAL(1,solution->updateCfl(prob));
}

void Test_Solution::test_increment() {
	ConstraintArgument * constArg = intVar1;
	Value* v = new Value(3);
	solution->modifValue(0,v);
	solution->increment(constArg, prob);
	CPPUNIT_ASSERT_EQUAL(1,solution->getValues()[0].first->getDomain()->getCfl()[3-1].second);
}

void Test_Solution::test_choice() {
	int iter = 5;	
	for(int i=0;i<iter;i++){
		solution->getValues()[0].first->getDomain()->incrementCfl(10);		
	}
	iter = 3;	
	for(int i=0;i<iter;i++){
		solution->getValues()[1].first->getDomain()->incrementCfl(15);		
	}
	CPPUNIT_ASSERT_EQUAL(1,solution->choice());
}
