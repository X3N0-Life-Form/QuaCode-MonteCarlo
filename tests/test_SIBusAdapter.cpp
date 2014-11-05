#include "test_SIBusAdapter.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_SIBusAdapter);

void Test_SIBusAdapter::setUp() {
  adapter = new SIBusAdapter();
}

void Test_SIBusAdapter::tearDown() {
  if (adapter != NULL) {
    delete(adapter);
  }
}

void Test_SIBusAdapter::test_GET_VALUE() {
  string regular("test(5)");
  string two("test(5,5)");
  //GET_VALUE(regular, s_reg);
  GET_VALUE(two, s_two);
  //CPPUNIT_ASSERT_EQUAL(string("5"), s_reg);
  CPPUNIT_ASSERT_EQUAL(string("5,5"), s_two);
}

void Test_SIBusAdapter::test_tokenize() {
  string test("5,4,6");
  vector<string> boundaries = tokenize(test, ",");
  CPPUNIT_ASSERT(boundaries.size() == 3);
}

void Test_SIBusAdapter::test_identifyQuantifier() {
  string e("E"), f("F"), nope("nope");
  CPPUNIT_ASSERT(EXISTS == adapter->identifyQuantifier(e));
  CPPUNIT_ASSERT(FORALL == adapter->identifyQuantifier(f));
  CPPUNIT_ASSERT_THROW(adapter->identifyQuantifier(nope), string);
}

void Test_SIBusAdapter::test_identifyType() {
  string i("I"), b("B"), nope("nope");
  CPPUNIT_ASSERT(INTEGER == adapter->identifyType(i));
  CPPUNIT_ASSERT(BOOLEAN == adapter->identifyType(b));
  CPPUNIT_ASSERT_THROW(adapter->identifyType(nope), string);
}

void Test_SIBusAdapter::test_identifyDomain() {
  string s_d1("interval(1,5)"),
    s_d2("interval(1,5)"),
    s_d3("interval(-2,2)"),
    nope("nope");
  Domain* d1 = adapter->identifyDomain(s_d1);
  Domain* d2 = adapter->identifyDomain(s_d2);
  Domain* d3 = adapter->identifyDomain(s_d3);
  // basic assertions
  CPPUNIT_ASSERT_THROW(adapter->identifyDomain(nope), string);
  CPPUNIT_ASSERT(d1 != NULL);
  CPPUNIT_ASSERT(d2 != NULL);
  CPPUNIT_ASSERT(d3 != NULL);
  CPPUNIT_ASSERT(d1->getFirstValue() == 1);
  CPPUNIT_ASSERT(d1->getLastValue() == 5);
  CPPUNIT_ASSERT(d3->getFirstValue() == -2);
  CPPUNIT_ASSERT(d3->getLastValue() == 2);
  // identity assertions
  CPPUNIT_ASSERT(d1 == d2);
  CPPUNIT_ASSERT(d1 != d3);
}

void Test_SIBusAdapter::test_identifyConstraintType() {
  string t_and("AND"), t_or("OR"), t_xor("XOR"),
    imp("IMP"), eq("EQ"), times("TIMES"), linear("LINEAR"),
    nope("nope");
  CPPUNIT_ASSERT_EQUAL(AND, adapter->identifyConstraintType(t_and));
  CPPUNIT_ASSERT_EQUAL(OR, adapter->identifyConstraintType(t_or));
  CPPUNIT_ASSERT_EQUAL(XOR, adapter->identifyConstraintType(t_xor));
  CPPUNIT_ASSERT_EQUAL(IMP, adapter->identifyConstraintType(imp));
  CPPUNIT_ASSERT_EQUAL(C_EQ, adapter->identifyConstraintType(eq));
  CPPUNIT_ASSERT_EQUAL(TIMES, adapter->identifyConstraintType(times));
  CPPUNIT_ASSERT_EQUAL(LINEAR, adapter->identifyConstraintType(linear));

  CPPUNIT_ASSERT_THROW(adapter->identifyConstraintType(nope), string);
}

void Test_SIBusAdapter::test_identifyComparisonType() {
  string nq("NQ"), eq("EQ"), lq("LQ"), le("LE"),
    gq("GQ"), gr("GR"), nope("nope");
  CPPUNIT_ASSERT_EQUAL(NQ, adapter->identifyComparisonType(nq));
  CPPUNIT_ASSERT_EQUAL(EQ, adapter->identifyComparisonType(eq));
  CPPUNIT_ASSERT_EQUAL(LQ, adapter->identifyComparisonType(lq));
  CPPUNIT_ASSERT_EQUAL(LE, adapter->identifyComparisonType(le));
  CPPUNIT_ASSERT_EQUAL(GQ, adapter->identifyComparisonType(gq));
  CPPUNIT_ASSERT_EQUAL(GR, adapter->identifyComparisonType(gr));

  CPPUNIT_ASSERT_THROW(adapter->identifyComparisonType(nope), string);
}

void Test_SIBusAdapter::test_identifyConstraintArgument() {
  Domain* di1 = new Domain(1, 5);
  Variable* v1 = VariableFactory::createVariable(EXISTS, INTEGER, "v1", di1);
  Variable* v2 = VariableFactory::createVariable(EXISTS, INTEGER, "v2", di1);
  string sv1("var(v1)"), sv2("var(v2)"),
    cst("int(5)"), i1("interval(1,5)"), i2("interval(1,2)");
  adapter->getProblem()->addVariable(v1);
  adapter->getProblem()->addVariable(v2);

  ConstraintArgument* resv1 = adapter->identifyConstraintArgument(sv1);
  ConstraintArgument* resv2 = adapter->identifyConstraintArgument(sv2);
  ConstraintArgument* rescst = adapter->identifyConstraintArgument(cst);
  ConstraintArgument* resi1 = adapter->identifyConstraintArgument(i1);
  ConstraintArgument* resi2 = adapter->identifyConstraintArgument(i2);

  CPPUNIT_ASSERT(v1 == resv1);
  CPPUNIT_ASSERT(v2 == resv2);
  Constant* constant = dynamic_cast<Constant*>(rescst);
  CPPUNIT_ASSERT(constant != NULL);
  Domain* dom = dynamic_cast<Domain*>(resi1);
  CPPUNIT_ASSERT(dom != NULL);
  CPPUNIT_ASSERT(*di1 == *dom);
  CPPUNIT_ASSERT(resi2 != NULL);
  Domain* di2 = dynamic_cast<Domain*>(resi2);
  CPPUNIT_ASSERT(di2 != NULL);
  CPPUNIT_ASSERT(1 == di2->getFirstValue());
  CPPUNIT_ASSERT(2 == di2->getLastValue());
}
