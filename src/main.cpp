#include "SIBusAdapter.h"

#include "solve/MonteCarloExplorer.h"
#include "solve/Explorer.h"
#include "solve/BooleanValidator.h"
#include "solve/IntegerValidator.h"
#include "solve/Validator.h"


#include "core/Domain.h"
#include "core/Value.h"
#include "core/Problem.h"
#include "core/Variable.h"
#include "core/factory/VariableFactory.h"
#include "core/Constraint.h"
#include "core/ConstraintArgument.h"
#include "core/Constant.h"



using namespace solve;
using namespace std;


int main(int argv, char** argc) {
	
	/*
	////////////////////////////////////////////
	//// heuristic - monte-carlo tests//////////
	////////////////////////////////////////////

	MonteCarloExplorer MCE = MonteCarloExplorer();
	cout << "test" << endl;
	cout << MCE.getTemperature() << endl;
	MCE.heuristic();
	cout << "test" << endl;
	cout << MCE.getTemperature() << endl;


	MonteCarloExplorer* myExplore = new MonteCarloExplorer();
	Domain* myDomain1 = new Domain(1,40);
	Domain* myDomain2 = new Domain(88,99);
	Domain* boolDomain = new Domain(0,1);

	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain1);
	Value vINT1 = myExplore->randDom(varINT1);
	cout<<"INT1 random value is "<<vINT1.getiValue()<<endl;

	Variable* varINT2 = VariableFactory::createVariable(EXISTS, INTEGER, "x2", myDomain2);
	Value vINT2 = myExplore->randDom(varINT2);
	cout<<"INT2 random value is "<<vINT2.getiValue()<<endl;

	Variable* varBOOL = VariableFactory::createVariable(EXISTS, BOOLEAN, "x3");
	Value vBOOL = myExplore->randDom(varBOOL);
	cout<<"BOOL random value is "<<vBOOL.getBValue()<<endl;
*/

	////////////////////////////////////////////
	//// validateConstraint  tests//////////
	////////////////////////////////////////////

	Problem* myProbleme = new Problem();

	MonteCarloExplorer* myExplore = new MonteCarloExplorer(myProbleme);
	Domain* myDomain = new Domain(1,40);
	Domain* TargetDomain1 = new Domain(21,25);
	Domain* TargetDomain2 = new Domain(29,30);
	Domain* TargetDomain3 = new Domain(390,400);

	Variable* varINT1 = VariableFactory::createVariable(EXISTS, INTEGER, "x1", myDomain);
	Variable* varINT2 = VariableFactory::createVariable(EXISTS, INTEGER, "x2", myDomain);
	Variable* varINT3 = VariableFactory::createVariable(FORALL, INTEGER, "x3", TargetDomain1);
	Variable* varINT4 = VariableFactory::createVariable(FORALL, INTEGER, "x4", TargetDomain2);
	Variable* varINT5 = VariableFactory::createVariable(FORALL, INTEGER, "x5", TargetDomain3);

	Value* vINT1 = new Value(myExplore->randDom(varINT1));
	Value* vINT2 = new Value(myExplore->randDom(varINT2));

	vector<Value* > forallInt3;
	for(int i=0;i<TargetDomain1->getSize();i++){
		forallInt3.push_back(new Value(TargetDomain1->getFirstValue()+i));
	}
	vector<Value* > forallInt4;
	for(int i=0;i<TargetDomain2->getSize();i++){
		forallInt4.push_back(new Value(TargetDomain2->getFirstValue()+i));
	}
	vector<Value* > forallInt5;
	for(int i=0;i<TargetDomain3->getSize();i++){
		forallInt5.push_back(new Value(TargetDomain3->getFirstValue()+i));
	}

	cout<<"x1 value is "<<vINT1->getiValue()<<endl;
	cout<<"x2 value is "<<vINT2->getiValue()<<endl;
	cout<<"x3 first value is "<<forallInt3[0]->getiValue()<<endl;
	cout<<"x4 last value is "<<forallInt4[TargetDomain2->getSize()-1]->getiValue()<<endl;
	cout<<"x5 last value is "<<forallInt5[TargetDomain3->getSize()-1]->getiValue()<<endl;

	Validator* intValidate = new IntegerValidator(myProbleme);
	Constraint* IntConstraint = new IntegerConstraint(LINEAR,LQ);
	IntConstraint->addArgument(varINT1);
	IntConstraint->addArgument(varINT2);
	IntConstraint->addArgument(varINT3);
	IntConstraint->addArgument(varINT4);
	IntConstraint->addArgument(varINT5);

	vector<pair<Variable *, Value *> > solution;
	solution.reserve(5);

		pair<Variable *, Value *> p;
		p.first = varINT1;
		p.second = vINT1;
 		solution.push_back(p);
		p.first = varINT2;
		p.second = vINT2;
		solution.push_back(p);
		p.first = varINT3;
		p.second = new Value(TargetDomain1->getFirstValue());
		solution.push_back(p);
		p.first = varINT4;
		p.second = new Value(TargetDomain2->getFirstValue());
		solution.push_back(p);
		p.first = varINT5;
		p.second = new Value(TargetDomain3->getFirstValue());
		solution.push_back(p);
	

		cout<<intValidate->validateConstraint(IntConstraint, solution)<<endl;

	for(unsigned int i = 1; i < 10; i++) {
				if (i < 9) {
					cout<<"i = "<<i<<endl;
				}
				else {
					cout<<"i = "<<i<< "fin!"<<endl;
				}
			}

	for(unsigned int i = 1; i < 10; i++) {
				if (!i == 9) {
					cout<<"i = "<<i<<endl;
				}
				else {
					cout<<"i = "<<i<< "fin!"<<endl;
				}
			}


	bool b1 = true ^ true;
	cout<<"b1 = "<<b1<<endl;

	bool b2 = true ^ false;
	cout<<"b2 = "<<b2<<endl;

	return 1;
}





