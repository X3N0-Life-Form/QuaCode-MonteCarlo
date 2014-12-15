#include "AdapterException.h"

using namespace std;

AdapterException::AdapterException(const std::string& message)
  : message(message) {
}

AdapterException::AdapterException(const char* message)
  : message(message) {
}

AdapterException::AdapterException(const char* message, std::string& data) 
  : message(string(message).append(data)) {
}


const char* AdapterException::what() const throw() {
  return message.c_str();
}
