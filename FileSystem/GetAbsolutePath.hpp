#pragma once

#include "IsRelativePath.hpp"
#include "GetCurrentWorkingDir.hpp"
#include <string> //class std::string

namespace FileSystem
{

/** Make inline to avoid multiple definitions linker error. */
inline std::string GetAbsolutePathA(const char * const path)
{
  std::string str;
  if( FileSystem::IsRelativePathA( path) )
  {
    std::string currentWorkingDir;
    OperatingSystem::GetCurrentWorkingDirA_inl(currentWorkingDir);
	str = currentWorkingDir + "/" + path;
  }
  return str;
}

};//namespace FileSystem
