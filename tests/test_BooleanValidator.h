#ifndef TEST_BOOLEANVALIDATOR_H
#define TEST_BOOLEANVALIDATOR_H

#include <cppunit/extensions/HelperMacros.h>

#include "../src/solve/BooleanValidator.h"
#include "../src/core/Problem.h"
#include "../src/core/Constant.h"

using namespace core;
using namespace solve;

class Test_BooleanValidator : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_BooleanValidator);

  CPPUNIT_TEST(test_validateConstraint);
  
  CPPUNIT_TEST_SUITE_END();
 private:
  Problem* prob;
  BooleanValidator* validator;
 public:
  void tearDown();
  void setUp();

  void test_validateConstraint();
 
  
};
#endif
