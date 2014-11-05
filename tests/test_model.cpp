#include "test_className.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_className);

void Test_className::setUp() {
  classConst = new className();
}

void Test_className::tearDown() {
  if (classConst != NULL) {
    delete(classConst);
  }
}

voidTest_className::test_funtion() {
 
}

