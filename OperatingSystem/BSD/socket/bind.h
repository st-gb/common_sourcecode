#pragma once///Include guard

#ifdef __linux__
  ///see http://pubs.opengroup.org/onlinepubs/009695399/functions/bind.html
  #include <sys/socket.h>///bind(...)
#endif
#if _WIN32///Microsoft Windows (also <> 32 bit)
  /**http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind :
   * "winsock.h (include Winsock2.h"*/
   #include <Winsock2.h>
#endif
