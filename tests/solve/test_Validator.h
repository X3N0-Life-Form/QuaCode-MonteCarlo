#ifndef TEST_VALIDATOR_H
#define TEST_VALIDATOR_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/solve/Validator.h"
#include "../../src/core/Problem.h"
#include "../../src/core/Constant.h"

using namespace core;
using namespace solve;

class Test_Validator : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Validator);

  CPPUNIT_TEST(test_getArgumentIValue);
  CPPUNIT_TEST(test_getArgumentBValue);
  CPPUNIT_TEST(test_getVariableValue);
  CPPUNIT_TEST(test_checkComparison);
  CPPUNIT_TEST(test_checkComparison_);
  
  CPPUNIT_TEST_SUITE_END();
 private:
  Problem* prob;
  Validator* validator;
 public:
  void tearDown();
  void setUp();

  void test_getArgumentIValue();
  void test_getArgumentBValue();
  void test_getVariableValue();
  void test_checkComparison();
  void test_checkComparison_();
  
};
#endif
