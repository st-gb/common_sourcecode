#pragma once///Include guard

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

bool isNonBlckngCnnctRtrnCode(){
  ///Under MS Windows errno is 0 and not "EINPROGRESS" after a blocking connect.
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
