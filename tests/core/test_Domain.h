#ifndef TEST_DOMAIN_H
#define TEST_DOMAIN_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/Domain.h"

using namespace core;

class Test_Domain : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Domain);

  CPPUNIT_TEST(test_getType);
  CPPUNIT_TEST(test_getFirstValue);
  CPPUNIT_TEST(test_getLastValue);
  CPPUNIT_TEST(test_getAlreadyChecked);

  CPPUNIT_TEST(test_getSizeAlreadyChecked);
  CPPUNIT_TEST(test_getSize);
  CPPUNIT_TEST(test_addValue);
  CPPUNIT_TEST(test_alreadyInto);

  CPPUNIT_TEST(test_getCfl);
  CPPUNIT_TEST(test_generateCflVector);
  CPPUNIT_TEST(test_initCfl);
  CPPUNIT_TEST(test_incrementCfl);
  CPPUNIT_TEST(test_setCflForValue);
  CPPUNIT_TEST(test_totalCfl);
  CPPUNIT_TEST(test_replace);
  CPPUNIT_TEST(test_sortedCfl);

  CPPUNIT_TEST_SUITE_END();
 private:
    Type type;
    // [firstValue; lastValue]
    int firstValue;
    int lastValue;
    int size;
    int* alreadyChecked;
    int sizeAlreadyChecked;
    Domain* domain;
    std::vector<std::pair<int, int> > cfl;
    
 public:
  void tearDown();
  void setUp();

  void test_getType();
  void test_getFirstValue();
  void test_getLastValue();
  void test_getAlreadyChecked();
  
  void test_getSizeAlreadyChecked();
  void test_getSize();
  void test_addValue();
  void test_alreadyInto();

  void test_getCfl();
  void test_generateCflVector();
  void test_initCfl();
  void test_incrementCfl();
  void test_setCflForValue();
  void test_totalCfl();
  void test_replace();
  void test_sortedCfl();

};
#endif
