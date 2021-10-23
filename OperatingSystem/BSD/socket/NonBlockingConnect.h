#pragma once///Include guard

#ifdef __cplusplus///enable both C and C++ 
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

///Detect if connected by calling "connect(...)" a 2nd time.
inline bool isCnnctdViaConnect(const int socketFileDescr,
  const struct sockaddr & serv_addr, socklen_t size)
{
  const int rslt = connect(socketFileDescr, & serv_addr, size);
  if(rslt == 0 && errno == EISCONN)
    return true;
  return false;
}

inline bool NonBlckingIsCnnctd(
  const int socketFileDescriptor,
  struct sockaddr & serv_addr,
  int srvAddrNumBytes,
  int & getpeernameErrNo)
{
  struct sockaddr clntAddr;
  socklen_t addrlen = sizeof(clntAddr);
/**https://stackoverflow.com/questions/17769964/linux-sockets-non-blocking-connect
 * Alexandre Fenyo Dec 12 '18 at 19:49 :
 * "When getsockopt(fd, SOL_SOCKET, SO_ERROR, ...) returns 0, with 0 in
 *  so_error, this does not mean that the socket is connected. This means
 *  no error occured until now. In this specific case, you need to call
 *  getpeername() and if getpeername() returns 0, this means the socket
 * is connected. If the socket is not connected, getpeername() returns
 * -1 with ENOTCONN in errno. getsockopt(fd, SOL_SOCKET, SO_ERROR, ...)
 * can inform you about a connection refused, but not about a connected
 * socket. You need to use getpeername() or other means to be sure the
 * socket is connected."
 * 
 * - answered Apr 12 '19 at 9:40 :
 * "There are a few ways to test if a nonblocking connect succeeds.
 * 1. call getpeername() first, if it failed with error ENOTCONN, the connection
 * failed. then call getsockopt with SO_ERROR to get the pending error on the
 * socket
 * 2. call read with a length of 0. if the read failed, the connection failed,
 * and the errno for read indicates why the connection failed; read returns 0 if
 * connection succeeds
 * 3. call connect again; if the errno is EISCONN, the connection is already
 * connected and the first connect succeeded. */
 /** getsockopt(fd, SOL_SOCKET, SO_ERROR, ...) stored 0 in param when connecting
   * to localhost. */
  int result = getpeername(socketFileDescriptor, &clntAddr, & addrlen );
  if(result == -1)
    getpeernameErrNo = errno;
  return result == 0;
}

#ifdef __cplusplus///enable both C and C++ 
}}}///end namespaces
#endif

