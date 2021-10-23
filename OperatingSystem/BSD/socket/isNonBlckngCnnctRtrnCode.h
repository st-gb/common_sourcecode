#pragma once///Include guard

#ifdef _WIN32
  ///isNonBlckngCnnctRtrnCode()
  #include <OperatingSystem/Windows/BSD_sockets/isNonBlckngCnnctRtrnCode.h>
#endif
#ifdef __linux__
  ///isNonBlckngCnnctRtrnCode()
  #include <OperatingSystem/POSIX/BSD_sockets/isNonBlckngCnnctRtrnCode.h>
#endif
