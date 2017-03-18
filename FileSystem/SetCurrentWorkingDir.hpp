/** This function is specific to an operating system.
 So place this file into the OperatingSystem folder? */
#pragma once /** include guard */

//int SetCurrentDirectory(const char *);

//int SetCurrentDirectory_inl(const char *);
#if defined(__unix__) //Linux, Android NDK
  #include <OperatingSystem/Linux/FileSystem/SetCurrentWorkingDir/SetCurrentWorkingDir.hpp>
  //#define OperatingSystem Linux
#endif
#ifdef _WIN32
  //#define Windows OperatingSystem
  #include <Windows/FileSystem/SetCurrentWorkingDir/SetCurrentWorkingDir.hpp>
#endif

namespace OperatingSystem
{
inline void SetCurrentWorkingDirA_inl(const char * ch)
{
#if defined(__unix__) //Linux, Android NDK
  Linux::SetCurrentWorkingDirA_inl(ch);
#endif
#ifdef _WIN32
  Windows::SetCurrentWorkingDirA_inl(ch);
#endif
}
}
