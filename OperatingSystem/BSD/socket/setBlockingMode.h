#pragma once///Include guard

#ifdef __linux__
  #include <OperatingSystem/POSIX/BSD_sockets/setBlockingMode.h>
#endif
#ifdef _WIN32
  #include <OperatingSystem/Windows/BSD_sockets/setBlockingMode.h>
#endif