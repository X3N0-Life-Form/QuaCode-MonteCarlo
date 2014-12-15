#include "test_IntegerVariable.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_IntegerVariable);

void Test_IntegerVariable::setUp() {
	quantifier = EXISTS;
	type = INTEGER;
	name = "var1";
	domain = new Domain(1,10);
	IntVariable = new IntegerVariable(quantifier,type,name,domain);
}

void Test_IntegerVariable::tearDown() {
  if (IntVariable != NULL) {
    delete(IntVariable);
  }
}

void Test_IntegerVariable::test_getType() {
	CPPUNIT_ASSERT_EQUAL(INTEGER,IntVariable->getType());
}
