#pragma once///Include guard

#ifdef __linux__
  #include <netdb.h>///gethostbyname(...)
#endif
#ifdef _WIN32
///https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-gethostbyname
  #include <Winsock2.h> //, Winsock.h ///gethostbyname(...)
#endif
