#ifndef TEST_INTEGERCONSTRAINT_H
#define TEST_INTEGERCONSTRAINT_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/IntegerConstraint.h"

using namespace core;

class Test_IntegerConstraint : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_IntegerConstraint);

  CPPUNIT_TEST(test_getType);

  CPPUNIT_TEST_SUITE_END();
 private:

  IntegerConstraint* IntConstraint;

 public:
  void tearDown();
  void setUp();

  void test_getType();

};
#endif
