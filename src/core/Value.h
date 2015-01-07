
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
  class Value {
  private:
    bool bValue;
    int iValue;
    Type varType;

  public:

    // Constructors/Destructors
    Value(int value);
    Value(bool value);
    virtual ~Value ( );

    // Public attribute accessor methods
    Type getVarType();
    bool getBValue();
    int getiValue();

    /**
     * Useful to get the value independently of its type.
     * Note: booleans will be returned as "1" or "0".
     */
    std::string getValueAsString() const;
    void copy(Value* val);
    bool operator==(Value& right);
  };
}; // end of package namespace

#endif // VALUE_H
