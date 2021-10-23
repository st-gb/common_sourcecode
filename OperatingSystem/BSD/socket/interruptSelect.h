#pragma once///Include guard

#ifdef __linux__
  ///interruptSelect(...)
  #include <OperatingSystem/POSIX/BSD_sockets/interruptSelect.h>
#endif
#ifdef _WIN32
  ///interruptSelect(...)
  #include <OperatingSystem/Windows/BSD_sockets/interruptSelect.h>
#endif
