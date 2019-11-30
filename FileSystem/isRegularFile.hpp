#pragma once///Include guard
///Tests whether regular file, i.e. no device file etc.
///see https://en.wikipedia.org/wiki/Unix_file_types#Regular_file
#ifdef __linux__
  #include <OperatingSystem/POSIX/FileSystem/isRegularFile.hpp>
#endif
#ifdef _WIN32
  #include <OperatingSystem/Windows/FileSystem/isRegularFile.hpp>
#endif
