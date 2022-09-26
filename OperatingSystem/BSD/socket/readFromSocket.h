///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.02Apr2022 by Stefan Gebauer(TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Bln=BerLiN
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/Guard*/
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#else
///Include guard supported by (nearly) all industry compilers:
  #ifndef TU_Bln361095BSDsktReadFromSocket_h
  #define TU_Bln361095BSDsktReadFromSocket_h
#endif

///Standard C(++) header files:
#include <inttypes.h>///uint8_t

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "recv_function.h"///recv(...)
#include <compiler/force_inline.h>///"TU_Bln361095frcInln" preprocessor macro
#include <hardware/CPU/fastest_data_type.h>///typedef fastestUnsignedDataType
///"TU_Bln361095MicrosoftWindows" preprocessor macro
#include <OperatingSystem/Windows/MicrosoftWindows.h>
///includes header files for "errno" and "WSAGetLastError()"
#include "GetLastError.h"
#include "socket.h"///TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd

/** For Microsoft Windows only "recv(...)" works (-1 as return value for
 *  "read(...)" ) */
/**http://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/posix-read
 * : "read(...)" is a POSIX function (not a Standard C function?).
 * http://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/read
 * : In contrast to "recv(...)" "_read(...)" sets only a little error codes:
 *  sets "errno" to EBADF, EINVAL.
 *  => So use recv(...) at least under MicroSoft Windows.*/
#define TU_Bln361095use_recv///Use "TU_Bln361095" prefix to ensure uniqueness.

#if defined TU_Bln361095MicroSoftWindows && ! defined TU_Bln361095use_recv
  #include <errno.h>///errno
#endif

#ifdef __cplusplus
TU_Bln361095BSDsktNmSpcBgn
#else
 #ifdef TU_Bln361095MicrosoftWindows
 /** http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
  * : "[out] char *buf" */
  typedef char * bufferType;
 #else
 /** http://pubs.opengroup.org/onlinepubs/009604599/functions/read.html :
  *  "read([...]void *buf"
  * http://pubs.opengroup.org/onlinepubs/007904975/functions/recv.html :
  * "recv([...]void *buffer" */
  typedef void * bufferType;
 #endif
#endif

/**@brief read from socket identified by {@link socketFileDesc}
 * @param socketFileDesc socket file descriptor. Should have been created by a
 *  call to socket(...) before, for example (indirectly) via
 *  "TU_Bln361095BSDsktUse(createSkt)".
 * @return > 0 on success:the number of received bytes
 *          < 0 on error */
#ifdef __cplusplus
///To enable both Windows and non-Windows version of recv(...).
template <typename bufferType>
#endif
TU_Bln361095frcInln///Make inline because only 1 function call.
int TU_Bln361095BSDsktDef(readFromSkt)(
  const int socketFileDesc,
  bufferType buffer,
  const int numBytesToRead)
{
  return
#ifdef TU_Bln361095use_recv
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
  /** http://linux.die.net/man/3/read : "Upon successful completion, read() and
   *  pread() shall return a non-negative integer indicating the number of
   *  bytes actually read. Otherwise, the functions shall return -1 and set
   *  errno to indicate the error."*/
    read
#endif
      (socketFileDesc,
#if defined TU_Bln361095MicroSoftWindows && defined TU_Bln361095use_recv
      (char*)
#endif
      buffer,
      numBytesToRead
#ifdef TU_Bln361095use_recv///Parameter only for recv(...)
      ,0/**flags*/
#endif
      );
}

/**@brief read from socket identified by {@link socketFileDesc}*/
#ifdef __cplusplus
///To enable both Windows and non-Windows version of recv(...).
template <typename bufferType>
#endif
inline
int ///skt=socket
TU_Bln361095BSDsktDef(readFromSkt2)(const int socketFileDesc, bufferType buffer,
  const int numBytesToRead, unsigned * p_numBytesRead, int * const p_readError)
{
  fastestUnsignedDataType currNumB_read = 0;
  int i;
  do{///Read multiple times because the (internal) buffer used by "read(...)"
    /// may store less bytes than the ones that have been sent.
    i = TU_Bln361095BSDsktUse(readFromSkt)(
      socketFileDesc,
      ((uint8_t *) buffer) + currNumB_read,
      numBytesToRead);
  
    if(i > - 1)
      currNumB_read += i;
    else
    {
      * p_numBytesRead = 0;
 #if defined TU_Bln361095MicroSoftWindows && defined TU_Bln361095use_recv
  /**Microsoft Windows' recv(...) uses "WSAGetLastError()" :
   * http://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/read
   *  "If no error occurs, recv returns the number of bytes received [...]
   *  Otherwise, a value of SOCKET_ERROR is returned, and a specific error code
   *  can be retrieved by calling WSAGetLastError."*/
      * p_readError = WSAGetLastError();
 #else
  /**Microsoft Windows' read (...) and Linux' read and recv use "errno" :
   * http://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/read
   *  : "sets errno to EBAD", "errno is set to EINVAL"
   * http://pubs.opengroup.org/onlinepubs/009604599/functions/read.html :
   * "errno set to [EINTR]", "set errno to [EAGAIN]", [...]
   * http://pubs.opengroup.org/onlinepubs/007904975/functions/recv.html :
   * "set errno to [EAGAIN] or [EWOULDBLOCK]", [...] */
      * p_readError = errno;
 #endif
      break;
    }
  }while(currNumB_read < numBytesToRead);
  * p_numBytesRead = currNumB_read;
  return i;
}

TU_Bln361095BSDsktNmSpcEnd

#ifndef TU_Bln361095usePrgmInclGrd
#endif///TU_Bln361095BSDsktReadFromSocket_h
#endif
