#ifndef TEST_VALUE_H
#define TEST_VALUE_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/Value.h"

using namespace core;

class Test_Value : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Value);

  CPPUNIT_TEST(test_getVarType);
  CPPUNIT_TEST(test_getBValue);
  CPPUNIT_TEST(test_getiValue);

  CPPUNIT_TEST_SUITE_END();
 private:
  bool bValue;
  int iValue;
  Type varType;
  Value* bv;
  Value* iv;
 public:
  void tearDown();
  void setUp();

  void test_getVarType();
  void test_getBValue();
  void test_getiValue();
  
};
#endif
