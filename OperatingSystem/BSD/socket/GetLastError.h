#pragma once///Include guard

#ifdef __linux__
  ///GetLastError(...)
  #include <OperatingSystem/POSIX/BSD_sockets/GetLastError.h>
#endif
#ifdef _WIN32
  ///GetLastError(...)
  #include <OperatingSystem/Windows/BSD_sockets/GetLastError.h>
#endif

