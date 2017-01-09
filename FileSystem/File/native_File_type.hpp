#pragma once

#ifdef _WIN32
  #include <Windows\FileSystem\File\File.hpp>
  typedef Windows_API::File native_File_type;
#endif
#ifdef __linux__
  #include <OperatingSystem/Linux/FileSystem/File/File.hpp>
  typedef Linux::File native_File_type;
#endif
