#pragma once //incl. guard

#ifndef LOCKABLE_FILE
#define LOCKABLE_FILE

#ifdef _WIN32
  #include <Windows/InputOutput/LockableFile.hpp>
#endif

class LockableFile
{
public:
  enum lockMode{ read}
  enum openMode { read};
  void OpenA(const char * const filePath, enum openMode, enum lockMode)
  {
    HANDLE CreateFileA(
      filePath //_In_      LPCSTR lpFileName,
      , read //GENERIC_READ //_In_      DWORD dwDesiredAccess,
      _In_      DWORD dwShareMode,
      _In_opt_  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
      _In_      DWORD dwCreationDisposition,
      _In_      DWORD dwFlagsAndAttributes,
      _In_opt_  HANDLE hTemplateFile
    )
  }
};

#endif