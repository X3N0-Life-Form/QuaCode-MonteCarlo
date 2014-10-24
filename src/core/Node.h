
#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <cstddef>
#include "Domain.h"

namespace core {


/**
  * class Node
  * 
  */
    template<class T>
    class Node
    {
      //friend class Domain;
      public:

        // Constructors/Destructors
        //Node ();
        Node(int id);
        //Node(Node<T>* parent, int id, Domain d,T data);
        virtual ~Node ();

        T& getData() const;
        int getId() const;
        //Domain getDomain() const;
        void setData(const T& data);
        void addChild(const int id, const T& data);
        void removeChild(const size_t& indx);
        Node<T>* findChild(const int id) const;
        Node<T>* getChild(const size_t& indx) const;
        Node<T>* getParent() const;
        int getNumChildren() const;
        bool isLeaf () const;
        void setLeaf(bool b);

      protected:
        bool leaf; // Flag to know if box is a leaf or not

      private:
        T* data; //value
        int id; //index of the current node
        //Domain d;
        Node<T>* parent;
        std::vector<Node<T>*> children;

    };
}; 

#endif // NODE_H
