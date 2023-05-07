#pragma once

///Standard C(++) library header files:
#include <string>///class std::string

///Microsoft Windows operating system specific header files:
#ifdef _MSC_VER///Microsoft (Visual C) compiler
/**Microsoft Visual Studio has compile errors when including <windef.h>
 * directly. So include <windows.h> (which includes <windef.h>) for DWORD*/
  #include <windows.h>///for DWORD
#else
  #include <windef.h>///for DWORD
#endif

std::string LocalLanguageMessageFromErrorCodeA(DWORD dwErrorCode) ;
std::string LocalLanguageMessageAndErrorCodeA(DWORD dwErrorCode) ;

std::string PossibleSolution(DWORD dwErrorCode) ;
