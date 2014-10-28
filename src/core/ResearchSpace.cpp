#include "ResearchSpace.h"

using namespace core;

// Constructors/Destructors
//  


template<class T>
ResearchSpace<T>::ResearchSpace (Node<T>* r) {
	this->root = r;
}

template<class T>
ResearchSpace<T>::ResearchSpace (Node<T>* r,std::vector<T> variables){
	this->root = r;
}

template<class T>
ResearchSpace<T>::~ResearchSpace () {}


