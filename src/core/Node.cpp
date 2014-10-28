

#include "Node.h"

using namespace core;

// Constructors/Destructors
//  //root of tree
template<class T>
Node<T>::Node () {
    this->id = -1;
}
//for test
template<class T>
Node<T>::Node(int id,T data) {
    this->data = data;
    this->id = id;
}


//other nodes
template<class T>
Node<T>::Node(Node<T>* parent, int id,T data) : parent(parent) {
    this->data = data;
    this->id = id;
}

template<class T>
Node<T>::~Node () { }

// get and set fonctions

template<class T>
T Node<T>::getData() const {
    return this->data;
}

template<class T>
int Node<T>::getId() const {
    return this->id;
}

template<class T>
void Node<T>::setData(const T data) {
    this->data = data;
}



//child fonction

template<class T>
void Node<T>::addChild(const int id, const T data) {
    children.push_back(new Node<T>(this, id, data));
}



template<class T>
void Node<T>::removeChild(const size_t& indx) {
    children.erase(children.begin()+indx);
}

template<class T>
void Node<T>::removeChild(const int id,const T data){
     for(int i=0; i<children.size(); i++)
        if(children[i]->getId() == id && children[i]->getData() == data)
            children.erase(children.begin()+i);
}

template<class T>
Node<T>* Node<T>::findChild(const int id, const T data) const {
    for(int i=0; i<children.size(); i++)
        if(children[i]->getId() == id && children[i]->getData() == data)
            return children[i];
    return NULL;
}

template<class T>
Node<T>* Node<T>::getChild(const size_t& indx) const {
    return children[indx];
}

template<class T>
Node<T>* Node<T>::getParent() const {
    return parent;
}

template<class T>
int Node<T>::getNumChildren() const {
    return children.size();
}


//leaf fonctions

template<class T>
bool Node<T>::isLeaf() {
    return this->leaf;
}


template<class T>
void Node<T>::setLeaf(bool b) {
   this->leaf = b;
}

//test
/*
int main(){
	//Domain d;
	
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
	return 1;
}
*/







