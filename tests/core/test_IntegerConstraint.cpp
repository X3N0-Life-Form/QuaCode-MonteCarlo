#include "test_IntegerConstraint.h"
#include "../../src/core/factory/VariableFactory.h"
#include "../../src/solve/IntegerValidator.h"
#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_IntegerConstraint);

void Test_IntegerConstraint::setUp() {
	IntConstraint = new IntegerConstraint(LINEAR,EQ);
}

void Test_IntegerConstraint::tearDown() {
  if (IntConstraint != NULL) {
    delete(IntConstraint);
  }
}

void Test_IntegerConstraint::test_getType() {
	CPPUNIT_ASSERT_EQUAL(INTEGER,IntConstraint->getType());
	
}

