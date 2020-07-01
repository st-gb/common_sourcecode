#pragma once///Include guard.

#include <errno.h>///error constants
#include <sstream>///class std::ostringstream

namespace OperatingSystem{namespace BSD{namespace sockets{

/** Errors specific to blocking connect(...), i.e. no 
 * "fcntl(socketFileDesc, F_SETFL, flags | O_NONBLOCK);" before connect(...) */
namespace BlockingCnnctError{///Error when calling a blocking connect(...), i.e.
//TODO errCode is specific to Unix
inline std::string GetPossibleCause_inl(const int errCode,const int port)
{
  std::ostringstream oss;
  /** LinuxMint 19 64 bit:
   *-"errno" was EINPROGRESS even when the host name did not exist.
   *-"errno" was EINPROGRESS when the send timed out (set via
   *    setsockopt(socketFileDesc, SOL_SOCKET, SO_SNDTIMEO,...) )
   *-"errno" was ETIMEDOUT when timeout via getsockopt(...) was 0 s 0 micros and
   *   not connected within ca. 90 s 
   * "errno" was ECONNREFUSED when no server listening */
  switch(errCode){
   case ECONNREFUSED:
    oss << "Possible causes:\n"
      "-no server listening on the remote address and port";
    break;
   case EINPROGRESS:
    oss << "Possible causes:\n"
      "-The firewall may block packets/connections. check your firewall "
      "settings for port " << port << "\n"
      "-timeout in send or receive (or connect) elapsed\n";
    break;
   case ETIMEDOUT:
    oss << "Possible causes:\n"
      "-no server on port " << port << " running.\n"
      "-server not reachable(router,(host) firewall,(router)port forwarding)\n";
    break;
  }
  return oss.str();
}
}///end namespace
}}}///end namespaces
