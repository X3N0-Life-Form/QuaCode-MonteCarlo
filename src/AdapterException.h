#ifndef ADAPTEREXCEPTION_H
#define ADAPTEREXCEPTION_H

#include <exception>
#include <string>

class AdapterException : public std::exception {
 private:
  const std::string& message;

 public:
  AdapterException(const std::string& message);
  AdapterException(const char* message);
  /**
   * Avoids having to manually append the error data to the message string.
   */
  AdapterException(const char* message, std::string& data);

  virtual const char* what() const throw();
};

#endif
