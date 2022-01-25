#pragma once///Include guard

/**Includes <winerror.h> for WSAEWOULDBLOCK, includes <Winsock2.h> for
 * WSAGetLastError(). */
#include <Winsock2.h>

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

bool isNonBlckngCnnctRtrnCode(){
  /** Under MS Windows "errno" is 0 and not "EINPROGRESS" as under Linux after a
   *  blocking connect. So use WSAGetLastError() instead. */
  /**https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
   * : "With a nonblocking socket, the connection attempt cannot be completed
   * immediately. In this case, connect will return SOCKET_ERROR, and
   * WSAGetLastError will return WSAEWOULDBLOCK. */
  int lastSockErr = WSAGetLastError();
  return lastSockErr == WSAEWOULDBLOCK;
}

#ifdef __cplusplus
}}}///end namespaces
#endif
