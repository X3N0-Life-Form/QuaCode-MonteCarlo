#include "test_Domain.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Domain);

void Test_Domain::setUp() {
	domain = new Domain(1,10);
}

void Test_Domain::tearDown() {
  if (domain != NULL) {
    delete(domain);
  }
}

void Test_Domain::test_getType() {
	CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_getFirstValue() {
	CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_getLastValue() {
	//CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_getAlreadyChecked() {
	//CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_getSizeAlreadyChecked() {
	//CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_getSize() {
	//CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_addValue() {
	//CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_alreadyInto() {
	//CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
}