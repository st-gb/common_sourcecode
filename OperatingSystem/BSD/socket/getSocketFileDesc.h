#pragma once///Include guard.

#include <sys/socket.h>///socket(...)

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#else
static///Neded for C
#endif
///Used by client and server for socket creation.
///Make inline because only 1 function call inside->no size benefit.
inline int GetSocketFileDesc(const int protoFam, const int type,
  const int proto)
{
  /** http://pubs.opengroup.org/onlinepubs/009695399/functions/socket.html :
   * "Upon successful completion, socket() shall return a non-negative integer, 
   * the socket file descriptor. Otherwise, a value of -1 shall be returned 
   * and errno set to indicate the error." */
  const int socketFileDesc = socket(
    /**http://man7.org/linux/man-pages/man2/socket.2.html:
    * AF_INET for IPv4 Internet protocols */protoFam, type,
    /** socket.h : "If PROTOCOL is zero, one is chosen automatically." */
    /**http://man7.org/linux/man-pages/man2/socket.2.html: 
     "Normally only a single protocol exists to support a
       particular socket type within a given protocol family, in which case
       protocol can be specified as 0."*/
    proto);
  return socketFileDesc;
}

#ifdef __cplusplus
}}}///end namespaces
#endif
