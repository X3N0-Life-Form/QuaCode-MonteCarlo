#ifndef TEST_SOLUTION_H
#define TEST_SOLUTION_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../src/core/Solution.h"
#include "../../src/solve/Validator.h"
#include "../../src/core/Problem.h"
#include "../../src/core/Constant.h"
#include "../../src/core/IntegerVariable.h"
#include "../../src/core/Constraint.h"

using namespace core;

class Test_Solution : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(Test_Solution);

  CPPUNIT_TEST(test_getValues);
  CPPUNIT_TEST(test_addValue);
  CPPUNIT_TEST(test_modifValue);
  CPPUNIT_TEST(test_generateValueVector);
  CPPUNIT_TEST(test_updateCfl);
  CPPUNIT_TEST(test_increment);
  CPPUNIT_TEST(test_choice);


  CPPUNIT_TEST_SUITE_END();
 private:
  Quantifier quantifier;
  Type type;
  std::string name1;
  std::string name2;
  Domain* domain;
  IntegerVariable* intVar1;
  IntegerVariable* intVar2;
  Problem* prob;
 	Solution* solution;
  std::vector<std::pair<Variable *, Value *> > values;
	Validator* validator;
	Constraint* cst;																																							
    
 public:
  void tearDown();
  void setUp();

  void test_getValues();
  void test_addValue();
  void test_modifValue();
  void test_generateValueVector();
  void test_updateCfl();
  void test_increment();
  void test_choice();


};
#endif