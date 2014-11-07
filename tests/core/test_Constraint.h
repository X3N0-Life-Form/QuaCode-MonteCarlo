#ifndef TEST_CONSTRAINT_H
#define TEST_CONSTRAINT_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/Constraint.h"

using namespace core;

class Test_Constraint : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Constraint);

  CPPUNIT_TEST(test_getConstraintType);
  CPPUNIT_TEST(test_getComparisonType);
  CPPUNIT_TEST(test_addANDgetArguments);

  CPPUNIT_TEST_SUITE_END();
 private:
  std::vector<ConstraintArgument *> arguments;
  constraint_type constraintType;
  comparison_type comparisonType;
  Constraint* constraint;

 public:
  void tearDown();
  void setUp();

  void test_getConstraintType();
  void test_getComparisonType();
  void test_addANDgetArguments();

};
#endif
