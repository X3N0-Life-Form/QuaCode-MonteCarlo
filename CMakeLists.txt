cmake_minimum_required(VERSION 2.8)

project("QuaCode-MonteCarlo")

set(CMAKE_VERBOSE_MAKEFILE true)

add_definitions(
  -Wall
  -O2
)

set(CORE_SRCS
  src/core/Problem.cpp
  src/core/Constraint.cpp
  src/core/IntegerConstraint.cpp
  src/core/BooleanConstraint.cpp
  src/core/Variable.cpp
  src/core/IntegerVariable.cpp
  src/core/BooleanVariable.cpp
  src/core/factory/VariableFactory.cpp
  src/core/Domain.cpp
  src/core/Value.cpp
  src/core/ResearchSpace.cpp
  src/core/Node.cpp
)

set(SOLVE_SRCS
  src/solve/Explorer.cpp
  src/solve/MonteCarloExplorer.cpp
  src/solve/Validator.cpp
  src/solve/BooleanValidator.cpp
  src/solve/IntegerValidator.cpp
)

add_executable(QC-MC
  src/main.cpp
  src/SIBusAdapter.cpp
  src/Manager.cpp
  ${CORE_SRCS}
  ${SOLVE_SRCS}
)
