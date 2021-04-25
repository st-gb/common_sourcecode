#pragma once///Include guard

/* Include this file in order to get OS-independent the socket(...)
 * declaration.*/

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif
enum errorCodes{connRefused, inProgress, timedOut,
 /** As return value if no other value fits. */ other};
#ifdef __cplusplus
}}}
#endif

#ifdef __linux__
  #include <OperatingSystem/POSIX/BSD_sockets/sockets.h>
#endif
#ifdef _WIN32
  #include <OperatingSystem/Windows/BSD_sockets/sockets.h>///InitSocket(...)
#endif

///For Windows only "recv(...)" works (-1 as return value for "read(...)" )
#define use_recv

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#else
 #ifdef _WIN32
  typedef char * bufferType;
 #else
  typedef void * bufferType;
 #endif
#endif

#ifdef __cplusplus
///To enable both Windows and non-Windows version of recv(...).
template <typename bufferType>
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
///To enable both Windows and non-Windows version of recv(...).
template <typename bufferType>
#endif
inline
int readFromSocket2(const int socketFileDesc, bufferType buffer,
  const int numBytesToRead, unsigned * p_numBytesRead)
{
  const int i = readFromSocket(socketFileDesc, buffer,
    numBytesToRead);
  if(i > - 1)
    * p_numBytesRead = i;
  else
    * p_numBytesRead = 0;
  return i;
}

#ifdef __cplusplus
}}}///end namespaces
#endif