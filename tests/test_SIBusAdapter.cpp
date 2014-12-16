#include "test_SIBusAdapter.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_SIBusAdapter);

void Test_SIBusAdapter::setUp() {
  adapter = new SIBusAdapter();
  adapter->setDisplayWarnings(false);
  toAdapter = new boost::interprocess::message_queue(
    boost::interprocess::open_or_create,
    SIBusAdapter::IPC_NAME_TO_ADAPTER,
    SIBusAdapter::MAX_MESSAGES,
    SIBusAdapter::MESSAGE_SIZE);
  fromAdapter =  new boost::interprocess::message_queue(
    boost::interprocess::open_or_create,
    SIBusAdapter::IPC_NAME_FROM_ADAPTER,
    SIBusAdapter::MAX_MESSAGES,
    SIBusAdapter::MESSAGE_SIZE);
}

void Test_SIBusAdapter::tearDown() {
  if (adapter != NULL) {
    delete(adapter);
  }
  if (toAdapter != NULL)
    delete(toAdapter);
  if (fromAdapter != NULL)
    delete(fromAdapter);
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
  string var_binder("VAR_BINDER   = var(E,I,h,interval(1:2))");
  vector<string> tokens = tokenize(var_binder, " ");
  CPPUNIT_ASSERT(tokens.size() == 3);
  CPPUNIT_ASSERT_EQUAL(string("VAR_BINDER"), tokens[0]);
  CPPUNIT_ASSERT_EQUAL(string("="), tokens[1]);
  CPPUNIT_ASSERT_EQUAL(string("var(E,I,h,interval(1:2))"), tokens[2]);
}

void Test_SIBusAdapter::test_identifyQuantifier() {
  string e("E"), f("F"), nope("nope");
  CPPUNIT_ASSERT(EXISTS == adapter->identifyQuantifier(e));
  CPPUNIT_ASSERT(FORALL == adapter->identifyQuantifier(f));
  CPPUNIT_ASSERT_THROW(adapter->identifyQuantifier(nope), AdapterException);
}

void Test_SIBusAdapter::test_identifyType() {
  string i("I"), b("B"), nope("nope");
  CPPUNIT_ASSERT(INTEGER == adapter->identifyType(i));
  CPPUNIT_ASSERT(BOOLEAN == adapter->identifyType(b));
  CPPUNIT_ASSERT_THROW(adapter->identifyType(nope), AdapterException);
}

void Test_SIBusAdapter::test_identifyDomain() {
  string s_d1("interval(1:5)"),
    s_d2("interval(1:5)"),
    s_d3("interval(-2:2)"),
    nope("nope");
  Domain* d1 = adapter->identifyDomain(s_d1);
  Domain* d2 = adapter->identifyDomain(s_d2);
  Domain* d3 = adapter->identifyDomain(s_d3);
  // basic assertions
  CPPUNIT_ASSERT_THROW(adapter->identifyDomain(nope), AdapterException);
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

  CPPUNIT_ASSERT_THROW(adapter->identifyConstraintType(nope), AdapterException);
}

void Test_SIBusAdapter::test_identifyComparisonType() {
  string nq("_NQ_"), eq("_EQ_"), lq("_LQ_"), le("_LE_"),
    gq("_GQ_"), gr("_GR_"), nope("nope");
  CPPUNIT_ASSERT_EQUAL(NQ, adapter->identifyComparisonType(nq));
  CPPUNIT_ASSERT_EQUAL(EQ, adapter->identifyComparisonType(eq));
  CPPUNIT_ASSERT_EQUAL(LQ, adapter->identifyComparisonType(lq));
  CPPUNIT_ASSERT_EQUAL(LE, adapter->identifyComparisonType(le));
  CPPUNIT_ASSERT_EQUAL(GQ, adapter->identifyComparisonType(gq));
  CPPUNIT_ASSERT_EQUAL(GR, adapter->identifyComparisonType(gr));

  CPPUNIT_ASSERT_THROW(adapter->identifyComparisonType(nope), AdapterException);
}

void Test_SIBusAdapter::test_identifyConstraintArgument() {
  Domain* di1 = new Domain(1, 5);
  Variable* v1 = VariableFactory::createVariable(EXISTS, INTEGER, "v1", di1);
  Variable* v2 = VariableFactory::createVariable(EXISTS, INTEGER, "v2", di1);
  string sv1("var(v1)"), sv2("var(v2)"),
    cst("int(5)"), i1("interval(1:5)"), i2("interval(1:2)");
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

void Test_SIBusAdapter::test_dealWithInputData_var() {
  adapter->dealWithInputData("VAR_BINDER = var(E,I,test,interval(1:3))");
  Variable* var = adapter->getProblem()->getVariables()[0];
  CPPUNIT_ASSERT(var != NULL);
  CPPUNIT_ASSERT_EQUAL(string("test"), var->getName());
  CPPUNIT_ASSERT(EXISTS == var->getQuantifier());
  CPPUNIT_ASSERT(INTEGER == var->getType());
  Domain* dom = var->getDomain();
  CPPUNIT_ASSERT(dom != NULL);
  CPPUNIT_ASSERT(dom->getFirstValue() == 1);
  CPPUNIT_ASSERT(dom->getLastValue() == 3);
}

void Test_SIBusAdapter::test_dealWithInputData_var_aux() {
  adapter->dealWithInputData("VAR_AUX = var(E,I,test)");
  Variable* var = adapter->getProblem()->getVariables()[0];
  CPPUNIT_ASSERT(var != NULL);
  CPPUNIT_ASSERT_EQUAL(string("test"), var->getName());
  CPPUNIT_ASSERT(EXISTS == var->getQuantifier());
  CPPUNIT_ASSERT(INTEGER == var->getType());
}

void Test_SIBusAdapter::test_dealWithInputData_constraint_OK() {
  Domain* d1 = new Domain(1,5);
  Variable* v1 = VariableFactory::createVariable(EXISTS, INTEGER, "v1", d1);
  Variable* v2 = VariableFactory::createVariable(EXISTS, INTEGER, "v2", d1);
  Constant* res = new Constant(new Value(3));
  adapter->getProblem()->addVariable(v1);
  adapter->getProblem()->addVariable(v2);
  //adapter->getProblem()->addVariable(res);

  try {
    adapter->dealWithInputData("CONSTRAINT = TIMES _EQ_ var(v1) var(v2) int(3)");
  } catch (string e) {
    cout<<endl<<e<<endl;
  }

  Constraint* constraint = adapter->getProblem()->getConstraints()[0];
  CPPUNIT_ASSERT(constraint != NULL);
  Variable* cv1 = dynamic_cast<Variable*>(constraint->getArguments()[0]);
  Variable* cv2 = dynamic_cast<Variable*>(constraint->getArguments()[1]);
  Constant* cres = dynamic_cast<Constant*>(constraint->getArguments()[2]);
  CPPUNIT_ASSERT(cv1 != NULL);
  CPPUNIT_ASSERT(cv2 != NULL);
  CPPUNIT_ASSERT(cres != NULL);
  CPPUNIT_ASSERT(*v1 == *cv1);
  CPPUNIT_ASSERT(*v2 == *cv2);
  CPPUNIT_ASSERT(*res == *cres);
}

void Test_SIBusAdapter::test_dealWithInputData_constraint_missingVar() {
  Domain* d1 = new Domain(1,5);
  Variable* v1 = VariableFactory::createVariable(EXISTS, INTEGER, "v1", d1);
  //Variable* v2 = VariableFactory::createVariable(EXISTS, INTEGER, "v2", d1);
  adapter->getProblem()->addVariable(v1);

  CPPUNIT_ASSERT_THROW(
    adapter->dealWithInputData(
      "CONSTRAINT = TIMES _EQ_ var(v1) var(v2) int(3)"),
    AdapterException
  );
}

void Test_SIBusAdapter::test_dealWithInputData_badData() {
  CPPUNIT_ASSERT_NO_THROW(adapter->dealWithInputData("bad data"));
}

void Test_SIBusAdapter::test_sendSwapAsk() {
  Domain* d1 = new Domain(1,5);
  Variable* v1 = VariableFactory::createVariable(EXISTS, INTEGER, "v1", d1);
  adapter->getProblem()->addVariable(v1);
  Value* val1 = new Value(1);
  Value* val2 = new Value(3);

  adapter->sendSwapAsk(v1, *val1, *val2);
  std::string message;
  message.resize(SIBusAdapter::MESSAGE_SIZE);
  unsigned int receivedSize, priority;
  fromAdapter->receive(&message[0], SIBusAdapter::MESSAGE_SIZE, receivedSize, priority);

  string expected("SWAP_ASK         = idVar(v1) idVal(1) idVal(3)");
  message.resize(expected.size());
  CPPUNIT_ASSERT_EQUAL(expected, message);
}

void Test_SIBusAdapter::test_dealWithInput_messageReception() {
  Domain* d1 = new Domain(1,5);
  std::string s_var1("VAR_BINDER = var(E,I,var1,interval(1:5))");
  Variable* var1 = VariableFactory::createVariable(EXISTS, INTEGER, "var1", d1);

  toAdapter->send(s_var1.data(), s_var1.size(), 0);
  adapter->dealWithInput();

  Variable* v = NULL;
  for (Variable* currentVar : adapter->getProblem()->getVariables()) {
    if (currentVar->getName() == var1->getName()) {
      v = currentVar;
      break;
    }
  }
  CPPUNIT_ASSERT(v != NULL);
  CPPUNIT_ASSERT_EQUAL(EXISTS, v->getQuantifier());
  CPPUNIT_ASSERT_EQUAL(INTEGER, v->getType());
  CPPUNIT_ASSERT_EQUAL(d1->getFirstValue(), v->getDomain()->getFirstValue());
  CPPUNIT_ASSERT_EQUAL(d1->getLastValue(), v->getDomain()->getLastValue());
}

void Test_SIBusAdapter::test_dealWithInput_stateChange() {
  CPPUNIT_ASSERT(DATA == adapter->getState());
  std::string line("CLOSE_MODELING");
  adapter->dealWithInputData(line);
  CPPUNIT_ASSERT(SEARCH == adapter->getState());
}

void Test_SIBusAdapter::test_dealWithInputData_space() {
  //Domain* d1 = new Domain(1,5);
  std::string s_var1("VAR_BINDER = var(E, I, var1, interval(1:5))");
  //Variable* var1 = VariableFactory::createVariable(EXISTS, INTEGER, "var1", d1);

  adapter->dealWithInputData(s_var1);
  // if things go beyond this point, it's working.
}
