#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstddef>
#include <map>

#include "ResearchSpace.h"
#include "ResearchSpace.cpp"

#include "Node.h"
#include "Variable.h"

#include "IntegerVariable.h"
#include "IntegerVariable.cpp"
#include "Domain.cpp"
#include "Quantifier.h"
#include "ConstraintArgument.h"


using namespace core;
using std::string;
//using boost::

bool satisfy(int x1,int x2,int x3,int x4,int w1,int w2,int w3,int w4,int f){
    if(x1*w1+x2*w2+x3*w3+x4*w4==f){
        std::cout<<"f = "<<f<<std::endl;
        return true;
    }     
    else{
        std::cout<<"failed!"<<std::endl;
         return false;
    }
}

std::map<Variable*, int> recherche(std::vector<Variable*> v){
    std::map<Variable*, int> solution;
    //for(int it1=v[0]->)
    solution[v[0]]=10;
    std::cout<<"Valeur de "<<v[0]->getName()<<" est "<<solution.find(v[0])->second<<std::endl;
    return solution;
}

int main(){
/*
	Node<int>* root= new Node<int>();

    std::cout<<"root id is "<<root->getId()<<std::endl;

    root->addChild(1,10);
    Node<int>* N1= root->getChild(0);

	N1->addChild(2,45);
    N1->addChild(2,60);
    N1->addChild(2,75);
	
    Node<int>* N2= N1->getChild(0);
    Node<int>* N3= N1->getChild(1);

    std::cout<<"Node1's parent is Node"<<N1->getParent()->getId()<<std::endl;

	N1->setLeaf(false);
	std::cout<<"is a leaf or not "<<N1->isLeaf()<<std::endl;
	std::cout<<"old data = "<<N1->getData()<<std::endl;
	N1->setData(20);
	std::cout<<"new data = "<<N1->getData()<<std::endl;
	std::cout<<"id is "<<N1->getId()<<std::endl;

    std::cout<<"Node N1 has "<<N1->getNumChildren()<<" children."<<std::endl;
    std::cout<<"1eme child is "<<N2->getId()<<", "<<N2->getData()<<std::endl;
    std::cout<<"2eme child is "<<N3->getId()<<", "<<N3->getData()<<std::endl;

    std::cout<<"find child(2,60) of N1's children : "<<N1->findChild(2,60)->getId()<<", "<<N1->findChild(2,60)->getData()<<std::endl;
    std::cout<<"Node2's parent is Node"<<N2->getParent()->getId()<<std::endl;

    N1->removeChild(0);
    std::cout<<"Node N1 has "<<N1->getNumChildren()<<" children."<<std::endl;
    N1->removeChild(2,60);
    std::cout<<"Node N1 has "<<N1->getNumChildren()<<" children."<<std::endl;
 */  
/***********************************************************************************/
/*
    class variable
    {
    public:
    	variable(int inf,int sup,string name){
    		this->inf = inf;
    		this->sup = sup;
    		this->name = name;
    	}
    	void setINF(const int inf){
    		this->inf = inf;
    	}
    	void setSUP(const int sup){
    		this->sup = sup;
    	}
    	void setNAME(const string name){
    		this->name = name;
    	}
    	
    	
    	int getINF() const{
    		return this->inf;
    	}
    	int getSUP() const{
    		return this->sup;
    	}
    	string getNAME() const{
    		return this->name;
    	}
    private:
    	int inf;
    	int sup;
    	string name;
    };
 */  
    
    Domain* myDomain1 = new Domain(1,40);
    Domain* myDomain2 = new Domain(-1,1);
    Domain* myDomain3 = new Domain(40,40);
    std::vector<Variable*> v;
    v.reserve(9);  //fix size of vector v to 9
    IntegerVariable* x1 = new IntegerVariable(EXISTS, INTEGER, "x1", myDomain1);
    IntegerVariable* x2 = new IntegerVariable(EXISTS, INTEGER, "x2", myDomain1);
    IntegerVariable* x3 = new IntegerVariable(EXISTS, INTEGER, "x3", myDomain1);
    IntegerVariable* x4 = new IntegerVariable(EXISTS, INTEGER, "x4", myDomain1);

    IntegerVariable* w1 = new IntegerVariable(EXISTS, INTEGER, "w1", myDomain2);
    IntegerVariable* w2 = new IntegerVariable(EXISTS, INTEGER, "w2", myDomain2);
    IntegerVariable* w3 = new IntegerVariable(EXISTS, INTEGER, "w3", myDomain2);
    IntegerVariable* w4 = new IntegerVariable(EXISTS, INTEGER, "w4", myDomain2);

    IntegerVariable* f = new IntegerVariable(FORALL, INTEGER, "f", myDomain3);

    /*
    variable var2(1,40,"x2");
    variable var3(1,40,"x3");
    variable var4(1,40,"x4");
    */
    v.push_back(x1);
    v.push_back(x2);
    v.push_back(x3);
    v.push_back(x4);

    v.push_back(w1);
    v.push_back(w2);
    v.push_back(w3);
    v.push_back(w4);

    v.push_back(f);

    /*
	Node<Variable*>* root= new Node<Variable*>();

    std::cout<<"root id is "<<root->getId()<<std::endl;
    
	ResearchSpace<variable>* mySpace1 = new ResearchSpace<variable>(root);
	ResearchSpace<variable>* mySpace2 = new ResearchSpace<variable>(root,v);
	
	Node<IntegerVariable*>* root= new Node<IntegerVariable*>();

    std::cout<<"root id is "<<root->getId()<<std::endl;
	ResearchSpace<IntegerVariable*>* mySpace1 = new ResearchSpace<IntegerVariable*>(root);
    root->addChild(0,x1);
    */

    

    recherche(v);

	return 1;
}




















