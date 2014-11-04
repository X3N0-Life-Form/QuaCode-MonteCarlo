#include "testTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestTests);

void TestTests::setUp() {
  testAttribute1 = 1;
  testAttribute2 = 2;
  testAttribute3 = new int(1);
}

void TestTests::tearDown() {
  delete(testAttribute3);
}

void TestTests::thisIsATest() {
  CPPUNIT_ASSERT(testAttribute1 != testAttribute2);
}

void TestTests::thisIsAnotherTest() {
  CPPUNIT_ASSERT(testAttribute3 != NULL);
}
