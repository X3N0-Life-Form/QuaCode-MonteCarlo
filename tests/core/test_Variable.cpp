#include "test_Variable.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Variable);

void Test_Variable::setUp() {
	quantifier = EXISTS;
	type = INTEGER;
	name = "var1";
	domain = new Domain(1,10);
	variable = new IntegerVariable(quantifier,type,name,domain);
}

void Test_Variable::tearDown() {
  if (variable != NULL) {
    delete(variable);
  }
}

void Test_Variable::test_getName() {
	CPPUNIT_ASSERT_EQUAL(name,variable->getName());
}

void Test_Variable::test_getDomain() {
 	CPPUNIT_ASSERT_EQUAL(domain,variable->getDomain());
}

void Test_Variable::test_getQuantifier() {
 	CPPUNIT_ASSERT_EQUAL(EXISTS,variable->getQuantifier());
}