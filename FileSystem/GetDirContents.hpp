#ifdef __linux__
  #include <OperatingSystem/POSIX/FileSystem/GetDirContents.hpp>
#endif
#ifdef _WIN32
  #include <OperatingSystem/Windows/FileSystem/GetDirContents.hpp>
#endif
