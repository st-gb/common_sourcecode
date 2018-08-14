#pragma once /** include guard */

#ifdef __linux__ /** POSIX/ Linux OS */
  #include "../POSIX/suspendExecution.hpp"
#endif
#ifdef _WIN32 /** Microsoft Windows */
  #include "../../Windows/time/suspendExecution.hpp"
#endif

/*namespace OperatingSystem {
  void sleep(int seconds);
  void suspendExecution(int seconds);
}*/