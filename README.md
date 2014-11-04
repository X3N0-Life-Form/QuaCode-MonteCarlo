QuaCode-MonteCarlo
==================

Compilation:
------------
Requirements:
  - cmake
  - [boost](http://www.boost.org/) (tested with boost 1.56) ---> [Getting Started - unix variants](http://www.boost.org/doc/libs/1_56_0/more/getting_started/unix-variants.html)
  - OR install through your system's package manager (`sudo apt-get install libboost-all-dev` on Ubuntu)
  - CPPUnit (`sudo apt-get install libcppunit-dev` on Ubuntu)

Instructions:
  - In the project root, call `cmake`
  - If the Makefile creation was successful, call `make`
  - The generated binary should be called `QC-MC`
  - The test runner binary is called `run_tests`

Notes:
------
  - UML diagrams realized using Umbrello.
  - `run_tests` will run every test if called without a test name