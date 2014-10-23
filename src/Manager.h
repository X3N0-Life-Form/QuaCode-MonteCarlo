
#ifndef MANAGER_H
#define MANAGER_H

#include "core/Problem.h"
#include "SIBusAdapter.h"

#include <string>
#include <vector>

using namespace core;

/**
  * class Manager
  * 
  */

class Manager
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Manager ( );

  /**
   * Empty Destructor
   */
  virtual ~Manager ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   */
  void initializeEverything ( )
  {
  }

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
  Problem* problem;
  SIBusAdapter* adapter;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};

#endif // MANAGER_H
