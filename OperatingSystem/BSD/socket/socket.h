#pragma once///Include guard

#ifdef __linux___
  #include <sys/socket.h>///socket(...)
  inline void InitSocket(){}
#endif
#ifdef _WIN32
///http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
///https://stackoverflow.com/questions/3531474/socklen-t-undeclared-when-compiling-c-code
  #include <winsock2.h>///socket(...), socklen_t
//  #include <Ws2ipdef.h>
  #include <ws2tcpip.h>///socklen_t
  #include <OperatingSystem/Windows/BSD_sockets/sockets.h>///InitSocket(...)
#endif

///For Windows only "recv(...)" works (-1 as return value for "read(...)" )
#define use_recv

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
///To enable both Windows and non-Windows version of recv(...).
template <typename bufferType>
#else
 #ifdef _WIN32
  typedef char * bufferType;
 #else
  typedef void * bufferType;
 #endif
#endif
inline
int readFromSocket(const int socketFileDesc, bufferType buffer,
  const int numBytesToRead)
{
  return
#ifdef use_recv
  /** http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
   * "If no error occurs, recv returns the number of bytes received and the
   * buffer pointed to by the buf parameter will contain this data received. If
   * the connection has been gracefully closed, the return value is zero.
   * Otherwise, a value of SOCKET_ERROR is returned, and a specific error code
   * can be retrieved by calling WSAGetLastError."*/
   /** http://man7.org/linux/man-pages/man2/recv.2.html :
    * recv(int sockfd, void *buf, size_t len, int flags); */
    recv
#else
    /** https://linux.die.net/man/3/read : "Upon successful completion, read()
     *  and pread() shall return a non-negative integer indicating the number 
     *  of bytes actually read. Otherwise, the functions shall return -1 and 
     *  set errno to indicate the error."*/
    read
#endif
      (socketFileDesc, 
#ifdef use_recv
 #ifdef _WIN32
      (char*)
 #endif
#endif
        buffer, 
      numBytesToRead
#ifdef use_recv
      ,0/**flags*/
#endif
      );
}

#ifdef __cplusplus
}}}///end namespaces
#endif