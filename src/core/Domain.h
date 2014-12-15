
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
    int size;
    int* alreadyChecked;
    int sizeAlreadyChecked;


  std::vector<std::pair<int, int> > cfl;
    
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
    int getSize();
    // add a value into alreadyChecked
    bool addValue(int value);
    bool alreadyInto(int value);

    std::vector<std::pair<int, int> > getCfl();

    void generateCflVector();

    void initCfl();

    void incrementCfl(int value);

    void setCflForValue(int value, int c);

    int totalCfl();

    // Operators
    virtual bool operator==(ConstraintArgument& right);
  };

}; // end of package namespace


#endif // DOMAIN_H
