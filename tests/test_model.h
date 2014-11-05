#ifndef TEST_ _H
#define TEST_ _H

#include <cppunit/extensions/HelperMacros.h>

#include "../src/className.h"

class Test_className : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_className );

  CPPUNIT_TEST();
  

  CPPUNIT_TEST_SUITE_END();
 private:
  className* adapter;
 public:
  void tearDown();
  void setUp();

  void functionName();
  
};
#endif
