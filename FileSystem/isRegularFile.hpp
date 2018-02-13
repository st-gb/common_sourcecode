
#ifdef __linux__
  #include <OperatingSystem/POSIX/FileSystem/isRegularFile.hpp>
#endif
#ifdef _WIN32
  #include <Windows/FileSystem/isRegularFile.hpp>
#endif