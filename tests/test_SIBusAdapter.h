#ifndef TEST_SIBUSADAPTER_H
#define TEST_SIBUSADAPTER_H

#include <cppunit/extensions/HelperMacros.h>

#include "../src/SIBusAdapter.h"

class Test_SIBusAdapter : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_SIBusAdapter);

  CPPUNIT_TEST(test_GET_VALUE);
  CPPUNIT_TEST(test_tokenize);
  CPPUNIT_TEST(test_identifyQuantifier);
  CPPUNIT_TEST(test_identifyType);
  CPPUNIT_TEST(test_identifyDomain);
  CPPUNIT_TEST(test_identifyConstraintType);
  CPPUNIT_TEST(test_identifyComparisonType);
  CPPUNIT_TEST(test_identifyConstraintArgument);
  CPPUNIT_TEST(test_dealWithInputData_var);
  CPPUNIT_TEST(test_dealWithInputData_var_aux);
  CPPUNIT_TEST(test_dealWithInputData_constraint_OK);
  CPPUNIT_TEST(test_dealWithInputData_constraint_missingVar);
  CPPUNIT_TEST(test_dealWithInputData_badData);
  //TO test: swap ask + send solution & other message_queue-related shit

  CPPUNIT_TEST_SUITE_END();
 private:
  SIBusAdapter* adapter;
 public:
  void tearDown();
  void setUp();

  void test_GET_VALUE();
  void test_tokenize();

  void test_identifyQuantifier();
  void test_identifyType();
  void test_identifyDomain();

  void test_identifyConstraintType();
  void test_identifyComparisonType();
  void test_identifyConstraintArgument();

  void test_dealWithInputData_var();
  void test_dealWithInputData_var_aux();
  void test_dealWithInputData_constraint_OK();
  void test_dealWithInputData_constraint_missingVar();
  void test_dealWithInputData_badData();
};
#endif
