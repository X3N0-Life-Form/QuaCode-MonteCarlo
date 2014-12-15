#include "test_BooleanVariable.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_BooleanVariable);

void Test_BooleanVariable::setUp() {
	quantifier = EXISTS;
	type = BOOLEAN;
	name = "var1";
	domain = new Domain(0,1);
	BoolVariable = new BooleanVariable(quantifier,type,name,domain);
}

void Test_BooleanVariable::tearDown() {
  if (BoolVariable != NULL) {
    delete(BoolVariable);
  }
}

void Test_BooleanVariable::test_getType() {
	CPPUNIT_ASSERT_EQUAL(BOOLEAN,BoolVariable->getType());
}
