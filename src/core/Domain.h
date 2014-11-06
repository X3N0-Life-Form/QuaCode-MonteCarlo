
#ifndef DOMAIN_H
#define DOMAIN_H

#include "../Type.h"
#include "ConstraintArgument.h"

#include <string>
#include <vector>


namespace core {


  /**
   * class Domain
   * 
   */
  class Domain : public ConstraintArgument {
  private:
    Type type;
    // [firstValue; lastValue]
    int firstValue;
    int lastValue;
    
    int* alreadyChecked;
    int sizeAlreadyChecked;
    
  public:
    // Constructors/Destructors
    Domain(int val1, int val2);
    virtual ~Domain ( );

    // getters and setters
    Type getType ( );
    int getFirstValue();
    int getLastValue();
    int * getAlreadyChecked();
    int getSizeAlreadyChecked();
    
    // add a value into alreadyChecked
    bool addValue(int value);
    bool alreadyInto(int value);

    // Operators
    virtual bool operator==(ConstraintArgument& right);
  };

}; // end of package namespace


#endif // DOMAIN_H
