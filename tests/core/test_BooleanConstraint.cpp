#include "test_BooleanConstraint.h"
#include "../../src/core/factory/VariableFactory.h"
#include "../../src/solve/IntegerValidator.h"
#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_BooleanConstraint);

void Test_BooleanConstraint::setUp() {
	BoolConstraint = new BooleanConstraint(OR,EQ);
}

void Test_BooleanConstraint::tearDown() {
  if (BoolConstraint != NULL) {
    delete(BoolConstraint);
  }
}

void Test_BooleanConstraint::test_getType() {
	CPPUNIT_ASSERT_EQUAL(BOOLEAN,BoolConstraint->getType());
	
}

