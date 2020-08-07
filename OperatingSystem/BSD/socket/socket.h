#pragma once///Include guard

#ifdef __linux___
  #include <sys/socket.h>///socket(...)
#endif
#ifdef _WIN32
///http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
///https://stackoverflow.com/questions/3531474/socklen-t-undeclared-when-compiling-c-code
  #include <winsock2.h>///socket(...), socklen_t
//  #include <Ws2ipdef.h>
  #include <ws2tcpip.h>///socklen_t
#endif
