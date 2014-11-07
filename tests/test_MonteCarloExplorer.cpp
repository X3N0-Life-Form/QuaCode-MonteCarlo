#include "test_MonteCarloExplorer.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_MonteCarloExplorer);

void Test_MonteCarloExplorer::setUp() {
  problem = new Problem();
  monteCarloExplore = new MonteCarloExplorer(problem);
}

void Test_MonteCarloExplorer::tearDown() {
  if (monteCarloExplore != NULL) {
    delete(monteCarloExplore);
  }
}

void Test_MonteCarloExplorer::test_getTemperature() {
	CPPUNIT_ASSERT_EQUAL(4.5,monteCarloExplore->getTemperature());
}

void Test_MonteCarloExplorer::test_getFrequence() {
	CPPUNIT_ASSERT_EQUAL(1000,monteCarloExplore->getFrequence());
}
void Test_MonteCarloExplorer::test_heuristic() {
	CPPUNIT_ASSERT_EQUAL(0,monteCarloExplore->heuristic());
}
void Test_MonteCarloExplorer::test_randDom() {
	Domain* intDomain = new Domain(40,40);
 	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", intDomain);
 	Value* vINT1 = new Value(40);

 	Domain* boolDomain = new Domain(1,1);
 	Variable* varBOOL = VariableFactory::createVariable(EXISTS, BOOLEAN, "x2", boolDomain);
 	Value* vBOOL = new Value(true);

 	CPPUNIT_ASSERT_EQUAL(vINT1->getiValue(),monteCarloExplore->randDom(varINT1)->getiValue());
 	CPPUNIT_ASSERT_EQUAL(vBOOL->getVarType(),monteCarloExplore->randDom(varBOOL)->getVarType());
}
void Test_MonteCarloExplorer::test_metropolis() {
	int delta = 45;
	CPPUNIT_ASSERT_EQUAL(true,monteCarloExplore->metropolis(delta));
	
}
void Test_MonteCarloExplorer::test_decreaseTemperature() {
	double t = monteCarloExplore->getTemperature();
	int iter = 10;
	while(iter>0){
		monteCarloExplore->decreaseTemperature();
		--iter;
	}
	CPPUNIT_ASSERT(t > monteCarloExplore->getTemperature());
}
