#pragma once

#include "IsRelativePath.hpp"
#include "GetCurrentWorkingDir.hpp"
#include <string> //class std::string

/** Make inline to avoid multiple definitions linker error. */
inline std::string GetAbsolutePathA(const char * const path)
{
  std::string str;
  if( FileSystem::IsRelativePathA( path) )
  {
    std::string currentWorkingDir;
    GetCurrentWorkingDirA_inl(currentWorkingDir);
	str = currentWorkingDir + path;
  }
  return str;
}
