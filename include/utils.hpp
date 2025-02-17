#ifndef __UTILS__H__
#define __UTILS__H__

#include "date/date.h"

namespace utilfunctions {
static inline std::chrono::_V2::system_clock::time_point CurrentTimeNS() {
  using namespace std::chrono;
  return system_clock::now();
}

}  // namespace utilfunctions

#endif  //!__UTILS__H__
