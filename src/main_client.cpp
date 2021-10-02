#include <iostream>
#include <mockserver.hpp>
#include <client.hpp>
#include "logger.hpp"

int main() {
  logger::loggerInitialize("./", "ClientTest.log");

  streamingclient client("127.0.0.1", 7777);
  client.Connect();
  const std::string message{"One"};
  while (1) {
    client.sendData(message);
    sleep(1);
  }
  std::cout << utilfunctions::CurrentTimeNS() << "\n";
  return 0;
}