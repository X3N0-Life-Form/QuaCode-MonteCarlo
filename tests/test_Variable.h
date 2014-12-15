#ifndef TEST_VARIABLE_H
#define TEST_VARIABLE_H

#include <cppunit/extensions/HelperMacros.h>

#include "../src/core/Variable.h"
#include "../src/core/IntegerVariable.h"

using namespace core;

class Test_Variable : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Variable);

  CPPUNIT_TEST(test_getName);
  CPPUNIT_TEST(test_getDomain);
  CPPUNIT_TEST(test_getQuantifier);

  CPPUNIT_TEST_SUITE_END();
 private:
  Variable* variable;
  Quantifier quantifier;
  Type type;
  std::string name;
  Domain* domain;
 public:
  void tearDown();
  void setUp();

  void test_getName();
  void test_getDomain();
  void test_getQuantifier();
  
};
#endif
