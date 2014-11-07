#ifndef TEST_INTEGERVALIDATOR_H
#define TEST_INTEGERVALIDATOR_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/solve/IntegerValidator.h"
#include "../../src/core/Problem.h"
#include "../../src/core/Constant.h"

using namespace core;
using namespace solve;

class Test_IntegerValidator : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_IntegerValidator);

  CPPUNIT_TEST(test_validateConstraint);
  
  CPPUNIT_TEST_SUITE_END();
 private:
  Problem* prob;
  IntegerValidator* validator;
 public:
  void tearDown();
  void setUp();

  void test_validateConstraint();
 
  
};
#endif
