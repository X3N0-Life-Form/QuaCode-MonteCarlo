
#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Type.h"
#include "Domain.h"
#include "Quantifier.h"
#include "ConstraintArgument.h"

#include <string>
#include <vector>


using namespace std;
namespace core {


/**
  * class Variable
  * 
  */
class Variable : public ConstraintArgument
{
public:

  // Constructors/Destructors
  //  
  Variable ( );
  Variable(Quantifier quant, Type type, std::string name, Domain* domain);
  virtual ~Variable ( );

  // Getters
  //
  virtual Type getType() = 0;
  string getName();
  Domain* getDomain();
  Quantifier getQuantifier();

private:
 
  Quantifier quantifier;
  Type type;
  std::string name;
  Domain* domain;

};
}; // end of package namespace

#endif // VARIABLE_H
