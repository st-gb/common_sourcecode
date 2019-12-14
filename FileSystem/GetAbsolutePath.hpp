#pragma once //include guard

#ifdef _WIN32 ///Microsoft Windows
  #include "../OperatingSystem/Windows/FileSystem/GetAbsolutePath.hpp"
#endif

#ifdef __linux__
  #include "../OperatingSystem/POSIX/FileSystem/GetAbsolutePath.hpp"
#endif
