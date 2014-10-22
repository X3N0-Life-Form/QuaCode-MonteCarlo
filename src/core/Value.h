
#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <vector>



namespace core {


/**
  * class Value
  * 
  */

class Value
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Value ( );

  /**
   * Empty Destructor
   */
  virtual ~Value ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  bool b_value;
  int i_value;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of b_value
   * @param new_var the new value of b_value
   */
  void setB_value ( bool new_var )   {
      b_value = new_var;
  }

  /**
   * Get the value of b_value
   * @return the value of b_value
   */
  bool getB_value ( )   {
    return b_value;
  }

  /**
   * Set the value of i_value
   * @param new_var the new value of i_value
   */
  void setI_value ( int new_var )   {
      i_value = new_var;
  }

  /**
   * Get the value of i_value
   * @return the value of i_value
   */
  int getI_value ( )   {
    return i_value;
  }
private:


  void initAttributes ( ) ;

};
}; // end of package namespace

#endif // VALUE_H
