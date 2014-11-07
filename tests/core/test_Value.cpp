#include "test_Value.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Value);

void Test_Value::setUp() {
	bValue = true;
	iValue = 10;
	bv = new Value(bValue);
	iv = new Value(iValue);	
}

void Test_Value::tearDown() {
  if (bv != NULL && iv != NULL) {
    delete(bv);
    delete(iv);
  }
}

void Test_Value::test_getVarType() {
	CPPUNIT_ASSERT_EQUAL(BOOLEAN,bv->getVarType());
	CPPUNIT_ASSERT_EQUAL(INTEGER,iv->getVarType());
}

void Test_Value::test_getBValue() {
 	CPPUNIT_ASSERT_EQUAL(true,bv->getBValue());
}

void Test_Value::test_getiValue() {
 	CPPUNIT_ASSERT_EQUAL(10,iv->getiValue());
}