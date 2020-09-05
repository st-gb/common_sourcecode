#pragma once///Include guard

///http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
///https://stackoverflow.com/questions/3531474/socklen-t-undeclared-when-compiling-c-code
#include <winsock2.h>///socket(...), socklen_t
//#include <Ws2ipdef.h>
#include <ws2tcpip.h>///socklen_t

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

inline void CloseSocket(){
///https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup
  int ret = WSACleanup();
}

inline enum errorCodes
#ifdef __cplusplus
  GetLastError
#else
  GetLastBSDsockError
#endif
  (){
  const int error = WSAGetLastError();
  switch(error){
   case WSAECONNREFUSED:
     return connRefused;
   case WSAEINPROGRESS:
     return inProgress;
   case WSAETIMEDOUT:
     return timedOut;
  }
}

inline void InitSocket(){///Without initializing a WSA error occurred
///https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
  /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
  wVersionRequested = MAKEWORD(2, 2);
  err = WSAStartup(wVersionRequested, &wsaData);
}

#if __cplusplus
}}}///namespaces ends
#endif