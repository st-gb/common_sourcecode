#pragma once///Include guard

#ifdef __linux__
/**http://pubs.opengroup.org/onlinepubs/009695399/functions/gethostbyname.html
 * : includes <netdb.h> */
  #include <netdb.h>///gethostbyname(...)
#endif
#ifdef _WIN32
///https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-gethostbyname
  #include <Winsock2.h> //, Winsock.h ///gethostbyname(...)
#endif

#ifdef __cplusplus
//namespace OperatingSystem{namespace BSD{namespace sockets{
#endif
///https://linux.die.net/man/3/h_errno
enum gethostbynameRslt{gethostbynameSucceeded = 0, gethostbynameUnknownHost,
  gethostbynameOtherError, gethostbynameBeyondLast};
#ifdef __cplusplus
//};
#endif
