#pragma once

#include <windows.h>

namespace Windows
{
  void SetCurrentWorkingDirA_inl(const char * const p_chDir)
  {
    /*BOOL b =*/ ::SetCurrentDirectoryA(p_chDir);
  }
}
