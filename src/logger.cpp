#include "logger.hpp"

logger* logger::m_instance{nullptr};
std::fstream logger::m_logHandler;
std::mutex logger::m_fileMutex;

logger::logger(std::string_view path, std::string_view logName)
  {
    std::string&& fullpath = path.data();
    fullpath.append(logName.data());
    m_logHandler.open(fullpath, std::ios::ios_base::out);
  };
  
