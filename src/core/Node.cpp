#include "Node.h"

using namespace core;

// Constructors/Destructors
//  

//Node::Node ( ) {
//}

template<class T>
Node<T>::Node(int id) :  id(id) {
  
}

/*Node<T>::Node(Node<T>* parent, int id, Domain d,T data) : parent(parent) {
    this->data = new T(data);
    this->id = id;
    this->Domain = d;
}*/

template<class T>
Node<T>::~Node ( ) { }

template<class T>
T& Node<T>::getData() const {
    return *this->data;
}

template<class T>
int Node<T>::getId() const {
    return *this->id;
}
/*
Domain Node<T>::getDomain() const {
    return *this->domain;
}
*/
template<class T>
void Node<T>::setData(const T& data) {
    *this->data = data;
}

template<class T>
void Node<T>::addChild(const int id, const T& data) {
    children.push_back(new Node<T>(this, id, data));
}

template<class T>
void Node<T>::removeChild(const size_t& indx) {
    children.erase(children.begin()+indx);
}

template<class T>
Node<T>* Node<T>::findChild(const int id) const {
    for(int i=0; i<children.size(); i++)
        if(children[i]->getId() == id)
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

template<class T>
bool Node<T>::isLeaf() const {
    return *this->leaf;
}

template<class T>
void Node<T>::setLeaf(bool b) {
    *this->leaf = b;
}
