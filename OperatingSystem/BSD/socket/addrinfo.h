#pragma once///Include guard

#ifdef __linux__
  #include <netdb.h>///struct addrinfo
#endif

#ifdef _WIN32
/**http://docs.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
 * : "Header 	ws2def.h"*/
  #include <ws2def.h>///struct addrinfo
#endif

