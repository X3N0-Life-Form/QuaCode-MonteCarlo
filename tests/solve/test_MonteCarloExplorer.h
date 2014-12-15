#ifndef TEST_MONTECARLOEXPLORER_H
#define TEST_MONTECARLOEXPLORER_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/solve/MonteCarloExplorer.h"
#include "../../src/core/Problem.h"
#include "../../src/core/Constant.h"

using namespace core;
using namespace solve;

class Test_MonteCarloExplorer : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_MonteCarloExplorer);

  CPPUNIT_TEST(test_getTemperature);
  CPPUNIT_TEST(test_getFrequence);
  CPPUNIT_TEST(test_heuristic);
  CPPUNIT_TEST(test_randDom);
  CPPUNIT_TEST(test_metropolis);
  CPPUNIT_TEST(test_decreaseTemperature);
  
  CPPUNIT_TEST_SUITE_END();
 private:
  Problem * problem;
  MonteCarloExplorer * monteCarloExplore;
 public:
  void tearDown();
  void setUp();

  void test_getTemperature();
  void test_getFrequence();
  void test_heuristic();
  void test_randDom();
  void test_metropolis();
  void test_decreaseTemperature();
  
};
#endif
