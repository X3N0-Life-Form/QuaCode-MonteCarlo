#ifndef TESTTESTS_H
#define TESTTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class TestTests : public CppUnit::TestFixture {
  // Test suite macros
  CPPUNIT_TEST_SUITE(TestTests);

  // list of test methods
  CPPUNIT_TEST(thisIsATest);
  CPPUNIT_TEST(thisIsAnotherTest);

  CPPUNIT_TEST_SUITE_END();

 private:
  int testAttribute1;
  int testAttribute2;
  int* testAttribute3;
 public:
  void setUp();
  void tearDown();
  void thisIsATest();
  void thisIsAnotherTest();
};

#endif
