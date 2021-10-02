#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <fstream>
#include <iostream>
#include <mutex>

#include "utils.hpp"

using namespace date;

#define LOG(message)  logger::logEvent(message) ;

class logger {
 private:
  /* data */
  static std::fstream m_logHandler;
  static logger* m_instance;
  static std::mutex m_fileMutex;
  logger(std::string_view path, std::string_view logName);

 public:
  logger(const logger&) = delete;
  logger& operator=(const logger&) = delete;
  logger(const logger&&) = delete;
  logger& operator=(const logger&&) = delete;
  static void loggerInitialize(std::string_view path = "./", std::string_view logName = "today.log"){
    std::scoped_lock<std::mutex> lock{m_fileMutex};
    if(!m_instance){   
      m_instance = new logger(path, logName);
    }
    else{
      std::cerr << "Logger already Initialized";
    }
      return;
  };
  template<typename T>
  static void logEvent(const T& message) {
    if(m_instance){
      std::scoped_lock<std::mutex> lock{m_fileMutex};
      m_logHandler << utilfunctions::CurrentTimeNS() << "\t" << message
                   << std::endl;
      return;
    }
    std::cerr << "Logger Not Initialized" << std::endl;
  }
  ~logger(){m_logHandler.close();};
};


#endif  //!__LOGGER__H__