#pragma once///Include guard, see http://en.wikipedia.org/wiki/Include_guard

///http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
///https://stackoverflow.com/questions/3531474/socklen-t-undeclared-when-compiling-c-code
#include <winsock2.h>///socket(...), socklen_t
//#include <Ws2ipdef.h>
#include <ws2tcpip.h>///socklen_t
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include <OperatingSystem/BSD/socket/socket.h>
#include <compiler/force_inline.h>///force_inline

TU_Bln361095BSDsktNmSpcBgn

/** @brief End the usage of BSD sockets/Windows sockets(Winsock) for all threads
 *   of the operating system process which calls this function:
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup:
 *   "In a multithreaded environment, WSACleanup terminates Windows Sockets
 *    operations for all threads."
 * @return >0:WSAGetLastError() in case of error. So messages in different
 *  languages are possible via FormatMessage().Else 0.
 *  Return int because WSAGetLastError() also returns int:
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
 *  "int WSAGetLastError();"*/
int TU_Bln361095BSDsktDef(End)(){
/**
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup:
* -"The WSACleanup function terminates use of the Winsock 2 DLL (Ws2_32.dll)"
* -"int WSACleanup();"
* -"The return value is zero if the operation was successful. Otherwise, the
*  value SOCKET_ERROR is returned, and a specific error number can be retrieved
*  by calling WSAGetLastError."
* -"When it has completed the use of Windows Sockets, the application or DLL
*  must call WSACleanup to deregister itself from a Windows Sockets
*  implementation and allow the implementation to free any resources allocated
*  on behalf of the application or DLL."*/
  int ret = WSACleanup();
  if(ret == SOCKET_ERROR)
    return WSAGetLastError();
  return 0;
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

/** @brief Without initializing the Windows sockets error WSANOTINITIALISED
 *   (error code 10093) occurred when using Windows/BSD socket functions.
 * @return 0:success, else error code equal to WSAGetLastError(). So it can be
 *  printed in different languages via TU_Berlin361095BSDscktsUse(getErrorMsg())
 *  which uses "FormatMessage(...)":
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
 *  : "The FormatMessage function can be used to obtain the message string for
 *   the returned error." */
force_inline int TU_Bln361095BSDsktDef(Init)(){
/**
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup:
* "The WSAStartup function initiates use of the Winsock DLL by a process."*/
  WORD wVersionRequested;
  WSADATA wsaData;
/**
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
 : "Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h" */
  wVersionRequested = MAKEWORD(2, 2);
/**
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
 * :"int WSAStartup", "If successful, the WSAStartup function returns zero.
 *  Otherwise, it returns one of the error codes listed below.
 * 
 * The WSAStartup function directly returns the extended error code in the
 * return value for this function. A call to the WSAGetLastError function is not
 * needed and should not be used." */
  const int rslt = WSAStartup(wVersionRequested, &wsaData);
  return rslt;
}

TU_Bln361095BSDsktNmSpcEnd
