#pragma once///Include guard
/**https://man7.org/linux/man-pages/man2/connect.2.html :
 * "CONFORMING TO" POSIX.1-2001, POSIX.1-2008 -> into "POSIX" (sub)folder */

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

bool isNonBlckngCnnctRtrnCode(){
  ///This holds for Linux (tested):
  return errno == EINPROGRESS;/** For non-blocking _BSD_ sockets */
}

#ifdef __cplusplus
}}}///end namespaces
#endif
