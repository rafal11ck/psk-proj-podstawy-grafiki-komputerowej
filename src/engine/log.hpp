#ifndef LOG_HPP_
#define LOG_HPP_

#include <ostream>

namespace G {
extern std::ostream &logstream;
};

#define LOGINFON LOGINFO << '\n'

#define LOGINFO                                                                \
  G::logstream << "\033[35m" << __FILE_NAME__ << " \033[36m"                   \
               << __PRETTY_FUNCTION__ << "\033[0m "

#endif // LOG_HPP_
