#include <client.hpp>
#include <iostream>
#include <mockserver.hpp>

#include "logger.hpp"

int main() {
  logger::loggerInitialize("./", "sockettest.log");
  streamingserver server("127.0.0.1", 7777);
  server.Bind();
  std::cout << utilfunctions::CurrentTimeNS() << "\n";
  return 0;
}
