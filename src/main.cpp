#include "SIBusAdapter.h"

#include "solve/factory/ExplorerFactory.h"

using namespace std;

void liveTest();


int main(int argc, char** argv) {

  if (argc > 1 && string(argv[1]) == string("-live-test")) {
    cout << "Initializing live test";
    cout.flush();
    liveTest();
    cout << " - done" << endl;
    return 0;
  }

  cout << "Creating adapter object & starting thread";
  cout.flush();
  SIBusAdapter adapter;
  cout << " - done" << endl;
  cout << "Waiting for problem data..." << endl;
  while(adapter.getState() != SEARCH) {
    //do nothing
  }
  // all of problem's data should have been retrieved
  Explorer* explorer = ExplorerFactory::createExplorer(MONTECARLO, adapter.getProblem());
  explorer->setAdapter(&adapter);

  // begin search
  cout << "Starting Monte Carlo exploration" << endl;
  explorer->heuristic();

  return 0;
}

void liveTest() {
  boost::interprocess::message_queue transmitter(
    boost::interprocess::open_or_create,
    SIBusAdapter::IPC_NAME_TO_ADAPTER,
    SIBusAdapter::MAX_MESSAGES,
    SIBusAdapter::MESSAGE_SIZE);
  std::string testLine("Testing...");
  transmitter.send(testLine.data(), testLine.size(), 0);
  std::string s_v1("VAR_BINDER = var(E,I,v1,interval(1:5))");
  std::string s_v2("VAR_BINDER = var(E,I,v2,interval(1:5))");
  std::string s_c1("CONSTRAINT = TIMES _EQ_ var(v1) var(v2) int(3)");
  std::string s_mcomplete("CLOSE_MODELING");
  transmitter.send(s_v1.data(), s_v1.size(), 0);
  transmitter.send(s_v2.data(), s_v2.size(), 0);
  transmitter.send(s_c1.data(), s_c1.size(), 0);
  transmitter.send(s_mcomplete.data(), s_mcomplete.size(), 0);
}





