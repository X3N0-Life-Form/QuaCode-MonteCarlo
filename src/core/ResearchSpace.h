
#ifndef RESEARCHSPACE_H
#define RESEARCHSPACE_H

#include "Node.h"
#include "Node.cpp"
#include "Variable.h"
#include "Variable.cpp"

#include <string>
#include <vector>
using std::string;

namespace core {
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
/**
  * class ResearchSpace
  * 
  */
template<class T>
class ResearchSpace
{

public:

  // Constructors/Destructors
  //  
  ResearchSpace (Node<T>* r);

  ResearchSpace (Node<T>* r,std::vector<T> variables);

  virtual ~ResearchSpace ();



private:

  // Static Private attributes
  //  

  // Private attributes
  //  
  //Node<Variable>* root;
  Node<T>* root;


};
}; // end of package namespace

#endif // RESEARCHSPACE_H
