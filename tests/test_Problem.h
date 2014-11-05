#ifndef TEST_PROBLEM_H
#define TEST_PROBLEM_H

#include <cppunit/extensions/HelperMacros.h>

#include "../src/core/Problem.h"
#include "../src/core/factory/VariableFactory.h"
#include "../src/core/IntegerConstraint.h"
#include "../src/core/BooleanConstraint.h"

using namespace core;

class Test_Problem : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Problem);

  CPPUNIT_TEST(test_addANDgetVariable);
  CPPUNIT_TEST(test_addANDgetConstraint);
  CPPUNIT_TEST(test_getDomain);
  
  
  CPPUNIT_TEST_SUITE_END();
 private:
  Problem* prob;
  std::vector<Variable*> variables;
  std::vector<Constraint*> constraints;
 public:
  void tearDown();
  void setUp();

  void test_addANDgetVariable();
  void test_addANDgetConstraint();
  void test_getDomain();
 
  
};
#endif
