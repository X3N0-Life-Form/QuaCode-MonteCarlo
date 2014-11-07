#ifndef TEST_BOOLEANCONSTRAINT_H
#define TEST_BOOLEANCONSTRAINT_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/BooleanConstraint.h"

using namespace core;

class Test_BooleanConstraint : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_BooleanConstraint);

  CPPUNIT_TEST(test_getType);

  CPPUNIT_TEST_SUITE_END();
 private:

  BooleanConstraint* BoolConstraint;

 public:
  void tearDown();
  void setUp();

  void test_getType();

};
#endif
