#pragma once///Include guard
/** https://man7.org/linux/man-pages/man3/raise.3.html :
  * "CONFORMING TO POSIX.1-2001, POSIX.1-2008" -> into "POSIX" (sub)folder */

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

inline void interruptSelect(void * p_v){
  ///SIGUSR1 not available in MinGW
  raise(SIGUSR1);///This cancels the waiting in "select(...)".
}

#ifdef __cplusplus
}}}///end namespaces
#endif
