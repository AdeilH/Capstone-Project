#include <iostream>
#include "logger.hpp"
int main() {
  using namespace date;
  logger::loggerInitialize();
  logger::logEvent("This is to be logged");
  bool x = false;
  LOG(utilfunctions::CurrentTimeNS());
  std::cout << utilfunctions::CurrentTimeNS() << "\n";
  return 0;
}