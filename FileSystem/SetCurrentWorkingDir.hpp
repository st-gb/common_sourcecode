#pragma once

//int SetCurrentDirectory(const char *);

//int SetCurrentDirectory_inl(const char *);
#if defined(__unix__) //Linux, Android NDK
  #include <Linux/FileSystem/SetCurrentWorkingDir/SetCurrentWorkingDir.hpp>
  #define Linux OperatingSystem
#endif
#ifdef _WIN32
  #define Windows OperatingSystem
  #include <Windows/FileSystem/SetCurrentWorkingDir/SetCurrentWorkingDir.hpp>
#endif
