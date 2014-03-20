#pragma once

#include <windows.h>

namespace Windows
{
  /** Make inline, else linker error "multiple definition of 
  *  `OperatingSystem::SetCurrentWorkingDirA_inl(char const*)'" */
  inline void SetCurrentWorkingDirA_inl(const char * const p_chDir)
  {
    /*BOOL b =*/ ::SetCurrentDirectoryA(p_chDir);
  }
}
