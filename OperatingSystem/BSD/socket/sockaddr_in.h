#pragma once///Include guard

#ifdef __linux__
  #include <netinet/in.h>///struct sockaddr_in
#endif
#ifdef _WIN32
  #include <winsock2.h>///for definitions in Ws2ipdef.h
///http://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-sockaddr_in
  #include <Ws2ipdef.h>///struct sockaddr_in
#endif