#ifndef TEST_INTEGERVARIABLE_H
#define TEST_INTEGERVARIABLE_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/IntegerVariable.h"

using namespace core;

class Test_IntegerVariable : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_IntegerVariable);

  CPPUNIT_TEST(test_getType);

  CPPUNIT_TEST_SUITE_END();

 private:
  IntegerVariable* IntVariable;
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
