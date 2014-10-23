
#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Type.h"
#include "Domain.h"
#include "Quantifier.h"

#include <string>
#include <vector>


using namespace std;
namespace core {


/**
  * class Variable
  * 
  */

class Variable
{
public:

  // Constructors/Destructors
  //  

  Variable ( );

  Variable(Quantifier quant, Type type, std::string name, Domain* domain);
  
  virtual ~Variable ( );

  virtual Type getType ( ) = 0;
  string getName();
  Domain* getDomain();
  Quantifier getQuantifier();


private:
 
  std::string name;
  Domain* domain;
  Quantifier quantifier;
  Type type;
  



};
}; // end of package namespace

#endif // VARIABLE_H
