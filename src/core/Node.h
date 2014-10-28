
#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstddef>
//#include "Variable.h"
//#include "ResearchSpace.h"

namespace core {


/**
  * class Node
  * 
  */
    template<class T>
    class Node
    {
      
      public:

        // Constructors/Destructors
        Node ();
        //for test
        Node(int id, T data);
        Node(Node<T>* parent, int id, T data);
        virtual ~Node ();
        T getData() const;
        int getId() const;
        void setData(const T data);
        void setParent(Node<T>* p);
        
        void addChild(const int id, const T data);
        
        void removeChild(const size_t& indx);
        void removeChild(const int id,const T data);
        Node<T>* findChild(const int id,const T data) const;
        Node<T>* getChild(const size_t& indx) const;
        Node<T>* getParent() const;
        int getNumChildren() const;

        bool isLeaf ();
        void setLeaf(bool b);

      protected:
        bool leaf; // Flag to know if box is a leaf or not

      private:
        T data; //value
        int id; //index of the current variable
        //Domain d;
        Node<T>* parent;
        std::vector<Node<T>*> children;

    };
}; 

#endif // NODE_H
