#include "ExplorerFactory.h"

using namespace solve;

Explorer* ExplorerFactory::createExplorer(ExplorerType type, Problem* problem) {
  switch(type) {
    case MONTECARLO:
      return new MonteCarloExplorer(problem);
  }
}
