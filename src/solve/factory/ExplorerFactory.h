#ifndef EXPLORERFACTORY_H
#define EXPLORERFACTORY_H

#include "../MonteCarloExplorer.h"

namespace solve {

  enum ExplorerType {
    MONTECARLO
  };

  class ExplorerFactory {
  public:
    static Explorer* createExplorer(ExplorerType type, Problem* problem);
  };
};

#endif
