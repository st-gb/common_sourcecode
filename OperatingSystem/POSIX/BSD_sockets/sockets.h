#pragma once///Include guard

/** into POSIX folder because errno conforms to POSIX:
 * http://linux.die.net/man/3/errno */

#include <sys/socket.h>///socket(...)
#include <errno.h>///errno

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
}

inline void InitSocket(){}

#if __cplusplus
}}}///namespaces ends
#endif