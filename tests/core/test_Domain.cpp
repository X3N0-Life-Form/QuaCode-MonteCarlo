#include "test_Domain.h"

#include <iostream>

using namespace std;
using namespace core;

CPPUNIT_TEST_SUITE_REGISTRATION(Test_Domain);

void Test_Domain::setUp() {
	domain = new Domain(1,10);
}

void Test_Domain::tearDown() {
  if (domain != NULL) {
    delete(domain);
  }
}

void Test_Domain::test_getType() {
	CPPUNIT_ASSERT_EQUAL(INTEGER,domain->getType());
	
}
void Test_Domain::test_getFirstValue() {
	CPPUNIT_ASSERT_EQUAL(1,domain->getFirstValue());
	
}
void Test_Domain::test_getLastValue() {
	CPPUNIT_ASSERT_EQUAL(10,domain->getLastValue());
	
}
void Test_Domain::test_getAlreadyChecked() {
	CPPUNIT_ASSERT_EQUAL(0,domain->getAlreadyChecked()[0]);
	
}
void Test_Domain::test_getSizeAlreadyChecked() {
	CPPUNIT_ASSERT_EQUAL(0,domain->getSizeAlreadyChecked());
	
}
void Test_Domain::test_getSize() {
	CPPUNIT_ASSERT_EQUAL(10,domain->getSize());
	
}
void Test_Domain::test_addValue() {
	bool addfalse = domain->addValue(100);
	bool addtrue = domain->addValue(5);

	CPPUNIT_ASSERT_EQUAL(false,addfalse);
	CPPUNIT_ASSERT_EQUAL(true,addtrue);
	CPPUNIT_ASSERT_EQUAL(1,domain->getSizeAlreadyChecked());
	CPPUNIT_ASSERT_EQUAL(5,domain->getAlreadyChecked()[domain->getSizeAlreadyChecked()-1]);
}
void Test_Domain::test_alreadyInto() {
	domain->addValue(3);
	CPPUNIT_ASSERT_EQUAL(true,domain->alreadyInto(3));
}

void Test_Domain::test_getCfl() {
	domain->initCfl();
	CPPUNIT_ASSERT_EQUAL(0,domain->getCfl()[0].second);
}

void Test_Domain::test_generateCflVector() {
	CPPUNIT_ASSERT_EQUAL(10,domain->getCfl()[9].first);
}

void Test_Domain::test_initCfl() {
	domain->initCfl();
	CPPUNIT_ASSERT_EQUAL(0,domain->getCfl()[0].second);
}

void Test_Domain::test_incrementCfl() {
	int iter = 5;
	for(int i=0;i<iter;i++){
		domain->incrementCfl(10);
	}	
	CPPUNIT_ASSERT_EQUAL(iter,domain->getCfl()[9].second);
}

void Test_Domain::test_setCflForValue() {
	int index = 9;
	int value = 4;
	domain->setCflForValue(index,value);
	CPPUNIT_ASSERT_EQUAL(value,domain->getCfl()[index-1].second);
}

void Test_Domain::test_totalCfl() {
	int v1 = 5;
	int v2 = 3;
	for(int i=0;i<v1;i++){
		domain->incrementCfl(10);
	}
	for(int i=0;i<v2;i++){
		domain->incrementCfl(1);
	}
	
	CPPUNIT_ASSERT_EQUAL(v1+v2,domain->totalCfl());
}

void Test_Domain::test_replace() {
	for(int index = 0;index<domain->getCfl().size();index++){
		int value = 4;
		domain->setCflForValue(index+1,value);
	}
	std::vector<std::pair<int, int> > vect;
	for (int i = 0; i <= 9; i++) {
    	vect.push_back(std::pair<int, int>(i, 0));
  	}
	for(int i = 0; i < vect.size(); i++) {		   
		    vect[i].first=i+1;
    		vect[i].second=i+1;
 	}
	 //replace 	cfl[0]<1,4>
	 //			cfl[1]<2,4>
	 //			cfl[2]<3,4>
 	 //			...     
 	 //			cfl[9]<10,4>

 	 //to
 	 // 		cfl[0]<1,1>
	 //			cfl[1]<2,2>
	 //			cfl[2]<3,3>
 	 //			...     
 	 //			cfl[9]<10,10>
 	domain->replace(vect);
 	int value;
 	for(int index = 0;index<domain->getCfl().size();index++){
 		value = domain->getCfl()[index].second;
		CPPUNIT_ASSERT_EQUAL(index+1,value);
	}
}

void Test_Domain::test_sortedCfl() {
	
		int index;
		int value=10;
		for(index=1;index<=domain->getCfl().size();index++){
			domain->setCflForValue(index,value);
			value--;
		}		
		value = 10;
		for(int i=0;i<domain->getCfl().size();i++){
			CPPUNIT_ASSERT_EQUAL(value,domain->sortedCfl()[i].first);
			CPPUNIT_ASSERT_EQUAL(i+1,domain->sortedCfl()[i].second);
			value--;
		}
}