
#ifndef VARIABLE_H
#define VARIABLE_H

#include "../Type.h"

#include <string>
#include <vector>



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


  /**
   * Empty Constructor
   */
  Variable ( );

  /**
   * Empty Destructor
   */
  virtual ~Variable ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @return Type
   */
  virtual Type getType ( ) = 0;

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

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};
}; // end of package namespace

#endif // VARIABLE_H
