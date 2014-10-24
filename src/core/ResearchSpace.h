
#ifndef RESEARCHSPACE_H
#define RESEARCHSPACE_H

#include "Node.h"
#include "Variable.h"

#include <string>
#include <vector>


namespace core {


/**
  * class ResearchSpace
  * 
  */

class ResearchSpace
{
public:

  // Constructors/Destructors
  //  
  ResearchSpace ( );

  virtual ~ResearchSpace ( );



private:

  // Static Private attributes
  //  

  // Private attributes
  //  
  Node<Variable>* root;



};
}; // end of package namespace

#endif // RESEARCHSPACE_H
