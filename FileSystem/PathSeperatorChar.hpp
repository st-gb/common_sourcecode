#pragma once

namespace FileSystem
{
  //static const char dirSeperatorChar;
  #if defined(__linux__)
  const char dirSeperatorChar = '/';
  const char dirSeperatorCharW = L'/';
#elif defined(_WIN32) //Windows 32 or 64 bit
  const char dirSeperatorChar = '\\';
  const char dirSeperatorCharW = L'\\';
#endif

};
