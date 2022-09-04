///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcOpSysWinBSDskt_isNonBlckngConnctRtrnCode_h
#define TU_Bln361095cmnSrcOpSysWinBSDskt_isNonBlckngConnctRtrnCode_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository:
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include "socket.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln

/**Includes <winerror.h> for WSAEWOULDBLOCK, includes <Winsock2.h> for
 * WSAGetLastError().*/
/*http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
* -"Minimum supported client  Windows 8.1, Windows Vista [desktop apps | UWP
*  apps"
* -"Minimum supported server  Windows Server 2003 [desktop apps | UWP apps]" */
#include <Winsock2.h>

TU_Bln361095BSDsktNmSpcBgn

/**Force inlining to avoid multiple definitions in different source files of the
 * same link target.*/
TU_Bln361095FrcInl bool TU_Bln361095BSDsktDef(isNonBlckngCnnctRtrnCode)(){
  /** Under MS Windows "errno" is 0 and not "EINPROGRESS" as under Linux after a
   *  blocking connect. So use WSAGetLastError() instead. */
/*http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
 * : "With a nonblocking socket, the connection attempt cannot be completed
 * immediately. In this case, connect will return SOCKET_ERROR, and
 * WSAGetLastError will return WSAEWOULDBLOCK." */
  const int lastBSDsktError = WSAGetLastError();
  return lastBSDsktError == WSAEWOULDBLOCK;
}

TU_Bln361095BSDsktNmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcOpSysWinBSDskt_isNonBlckngConnctRtrnCode_h
