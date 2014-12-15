#include "test_Constraint.h"
#include "../../src/core/factory/VariableFactory.h"
#include "../../src/solve/IntegerValidator.h"
#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Constraint);

void Test_Constraint::setUp() {
	constraint = new IntegerConstraint(LINEAR,EQ);
}

void Test_Constraint::tearDown() {
  if (constraint != NULL) {
    delete(constraint);
  }
}

void Test_Constraint::test_getConstraintType() {
	CPPUNIT_ASSERT_EQUAL(LINEAR,constraint->getConstraintType());
	
}

void Test_Constraint::test_getComparisonType() {
 	CPPUNIT_ASSERT_EQUAL(EQ,constraint->getComparisonType());
}

void Test_Constraint::test_addANDgetArguments() {
	Domain* myDomain = new Domain(1,40);
	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain);
	Variable* varINT2 = VariableFactory::createVariable(EXISTS, INTEGER, "x2", myDomain);
	constraint->addArgument(varINT1);
	constraint->addArgument(varINT2);
	Variable* var = dynamic_cast<Variable*>(constraint->getArguments()[1]);
 	CPPUNIT_ASSERT_EQUAL(varINT2->getName(),var->getName());
}
