#pragma once///Include guard

#ifdef __linux__
  #include <netinet/in.h>///struct sockaddr_in
#endif
#ifdef _WIN32
  #include <winsock2.h>///for definitions in Ws2ipdef.h
/**http://docs.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-sockaddr_in
 * : "Header winsock.h (include Ws2ipdef.h)" */
//  #include <Ws2Ipdef.h>///struct sockaddr_in
#endif