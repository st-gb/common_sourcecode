#pragma once///Include guard

///For possibilites see "answered Jun 21 '09 at 22:56" :
///https://stackoverflow.com/questions/7051844/how-to-find-the-full-path-of-the-c-linux-program-from-within
#ifdef __linux__
  #include "../Linux/Process/GetCurrExePath.hpp"
#endif
#ifdef _WIN32///Windows, also 64 bit
  //#include <OperatingSystem/Windows/Process/GetCurrExePath.h>
  #include <OperatingSystem/Windows/Process/FileSys/GetCurrProcessExeFileName.hpp>
#endif
