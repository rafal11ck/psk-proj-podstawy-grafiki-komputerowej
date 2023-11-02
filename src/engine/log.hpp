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

#define LOGWARNN LOGWARN << '\n'

#define LOGWARN                                                                \
  G::logstream << "\033[35m" << __FILE_NAME__ << " \033[36m"                   \
               << __PRETTY_FUNCTION__ << "\033[34m"                            \
               << " WARN"                                                      \
               << "\033[0m "

#ifdef TRACE
#define LOGTRACEN                                                              \
  G::logstream << "\033[35m" << __FILE_NAME__ << " \033[36m"                   \
               << "\033[0m " << __PRETTY_FUNCTION__ << " TRACE\n";
#else
#define LOGTRACEN
#endif // TRACE

#endif // LOG_HPP_
