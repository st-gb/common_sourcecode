///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcOpSysWindowsBSDskt_setBlckngMode_h
#define TU_Bln361095cmnSrcOpSysWindowsBSDskt_setBlckngMode_h

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include "socket.h"
#include <compiler/force_inline.h>///TU_Bln361095frcInln

TU_Bln361095BSDsktNmSpcBgn

/**Force inlining to prevent multiple definitions of this function in the link
 * target.*/
TU_Bln361095frcInln int TU_Bln361095BSDsktDef(SetBlckng)(
  const int socketFileDesc)
{
///http://stackoverflow.com/questions/9534088/using-winsock-for-socket-programming-in-c
///http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
  unsigned long off = 0;
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
 * : "Upon successful completion, the ioctlsocket returns zero. Otherwise, a
 * value of SOCKET_ERROR is returned, and a specific error code can be retrieved
 * by calling WSAGetLastError."*/
  int rtrnVal = ioctlsocket(socketFileDesc,
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
 * "[in] cmd" "A command to perform on the socket s."*/
/**http://www.ibm.com/support/knowledgecenter/SSB23S_1.1.0.2020/gtpc1/block.html
 * :"When FIONBIO is set, the socket is marked nonblocking."*/FIONBIO,
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
 * "[in, out] u_long *argp" "A pointer to a parameter for cmd."*/
    &off
    );
//  if(rtrnVal == 0)
  return rtrnVal;
}

/**Force inlining to prevent multiple definitions of this function in the link
 * target.*/
TU_Bln361095frcInln int TU_Bln361095BSDsktDef(SetNonBlckng)(
  const int socketFileDesc)
{
///http://stackoverflow.com/questions/9534088/using-winsock-for-socket-programming-in-c
///http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
  unsigned long on = 1;
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
 * : "Upon successful completion, the ioctlsocket returns zero. Otherwise, a
 * value of SOCKET_ERROR is returned, and a specific error code can be retrieved
 * by calling WSAGetLastError."*/
  int rtrnVal = ioctlsocket(socketFileDesc,
/**http://www.ibm.com/support/knowledgecenter/SSB23S_1.1.0.2020/gtpc1/block.html
 * :"When FIONBIO is set, the socket is marked nonblocking."*/FIONBIO,
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
 * "[in, out] u_long *argp" "A pointer to a parameter for cmd."*/
    &on);
  //if(rtrnVal == 0)
  return rtrnVal;
}

TU_Bln361095BSDsktNmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcOpSysWindowsBSDskt_setBlckngMode_h
