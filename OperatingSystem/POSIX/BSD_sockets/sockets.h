#pragma once///Include guard

/** This file belongs into POSIX folder because "errno" conforms to POSIX:
 * http://linux.die.net/man/3/errno */

#include <sys/socket.h>///socket(...)
#include <errno.h>///errno

/** Stefan Gebauer's common_sourcecode repository header files: */
///enum OperatingSystem::BSD::sockets::errorCodes
#include <OperatingSystem/BSD/socket/socket.h>

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

inline void CloseSocket(){}

inline enum errorCodes
#ifdef __cplusplus
  GetLastError
#else
  GetLastBSDsockError
#endif
  (){
  const int error = errno;
  switch(error){
   case ECONNREFUSED:
     return connRefused;
   case EINPROGRESS:
     return inProgress;
   case ETIMEDOUT:
     return timedOut;
  }
  return other;
}

inline void InitSocket(){}

#if __cplusplus
}}}///namespaces ends
#endif

