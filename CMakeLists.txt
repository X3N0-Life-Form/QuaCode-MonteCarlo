cmake_minimum_required(VERSION 2.8)

project("QuaCode-MonteCarlo")

set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_FLAGS "-std=c++0x")

add_definitions(
  -Wall
  -O2
)

#
# Main compilation
#

set(CORE_SRCS
  src/core/Problem.cpp
  src/core/Constraint.cpp
  src/core/IntegerConstraint.cpp
  src/core/BooleanConstraint.cpp
  src/core/factory/ConstraintFactory.cpp
  src/core/ConstraintArgument.cpp
  src/core/Variable.cpp
  src/core/IntegerVariable.cpp
  src/core/BooleanVariable.cpp
  src/core/factory/VariableFactory.cpp
  src/core/Constant.cpp
  src/core/Domain.cpp
  src/core/Value.cpp
  src/core/Solution.cpp
)

set(SOLVE_SRCS
  src/solve/Explorer.cpp
  src/solve/MonteCarloExplorer.cpp
  src/solve/Validator.cpp
  src/solve/BooleanValidator.cpp
  src/solve/IntegerValidator.cpp
)

set(QC-MC_DEPENDENCIES
  src/SIBusAdapter.cpp
  src/Manager.cpp
  ${CORE_SRCS}
  ${SOLVE_SRCS}
)

add_executable(QC-MC
  src/main.cpp
  ${QC-MC_DEPENDENCIES}
)

#
# Main linking
#

FIND_PACKAGE(Boost 1.49.0 COMPONENTS system thread)

target_link_libraries(QC-MC
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

#
# Unit testing
#

set(UNIT_TESTS
  tests/misc/testTests.cpp
  tests/test_SIBusAdapter.cpp

  tests/solve/test_Validator.cpp
  tests/solve/test_MonteCarloExplorer.cpp
  tests/solve/test_IntegerValidator.cpp
  tests/solve/test_BooleanValidator.cpp

  tests/core/test_Problem.cpp
  tests/core/test_Variable.cpp
  tests/core/test_Value.cpp
  tests/core/test_Constraint.cpp
  tests/core/test_IntegerConstraint.cpp
  tests/core/test_BooleanConstraint.cpp
)

add_executable(run_tests
  tests/test_runner.cpp
  ${UNIT_TESTS}
  ${QC-MC_DEPENDENCIES}

)
foreach(test ${UNIT_TESTS})
  add_test(NAME ${test} COMMAND run_tests)
endforeach(test)

#
# CppUnit linking
#

FIND_PATH(CPPUNIT_INCLUDE_DIRS cppunit/TestCase.h
  /usr/local/include
  /usr/include
)

FIND_LIBRARY(CPPUNIT_LIBRARIES cppunit
           ${CPPUNIT_INCLUDE_DIRS}/../lib
           /usr/local/lib
           /usr/lib
)

target_link_libraries(run_tests
  ${CPPUNIT_LIBRARIES}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)