#ifndef TEST_BOOLEANVARIABLE_H
#define TEST_BOOLEANVARIABLE_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/BooleanVariable.h"

using namespace core;

class Test_BooleanVariable : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_BooleanVariable);

  CPPUNIT_TEST(test_getType);

  CPPUNIT_TEST_SUITE_END();

 private:
  BooleanVariable* BoolVariable;
  Quantifier quantifier;
  Type type;
  std::string name;
  Domain* domain;
 public:
  void tearDown();
  void setUp();

  void test_getType();
  
};
#endif
