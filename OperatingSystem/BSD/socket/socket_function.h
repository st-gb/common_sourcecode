#pragma once///Include guard, see http://en.wikipedia.org/wiki/Include_guard

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095MicrosoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef TU_Bln361095MicrosoftWindows
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
 * : "Header winsock2.h"*/
 #include <winsock2.h>///socket(...),WSAGetLastError()
#else
/** http://pubs.opengroup.org/onlinepubs/009604499/functions/socket.html :
 *  "include <sys/socket.h>" */
  #include <sys/socket.h>///socket(...)
#endif