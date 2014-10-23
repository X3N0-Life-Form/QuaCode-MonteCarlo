
#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <vector>
#include "../Type.h"


namespace core {

/**
  * class Value
  * 
  */

  class Value
  {
  private:
    bool bValue;
    int iValue;
    Type varType;

  public:

    // Constructors/Destructors

    Value ( );
    virtual ~Value ( );

    // Public attribute accessor methods

    Type getVarType();
    bool getBValue();
    int getiValue();


  };
}; // end of package namespace

#endif // VALUE_H
