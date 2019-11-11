#pragma once //Include guard.

#include <string> //std::string
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <WinError.h> //ERROR_BAD_EXE_FORMAT
#endif //#ifdef _WIN32

class DLLloadError
{
public:
  static std::string GetPossibleSolution( DWORD dwWindowsErrorCode ) 
  {
    std::string strSol = "Possible solution(s):\n" ;
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
    switch( dwWindowsErrorCode )
    {
    case ERROR_INVALID_PARAMETER :
    case ERROR_BAD_EXE_FORMAT :
      strSol += "-this may be due to this is an unsupported binary file format "
        "(32 bit<->64 bit).\n"
        "So only attach 64 bit DLLs under 64 Bit Windows, 32 bit DLLs under "
        "32 Bit Windows\n" ;
      break ;
    case ERROR_MOD_NOT_FOUND:
      strSol += "-the dynamic library possibly depends on other modules/ "
        "dynamic libraries.\n"
        "Examine the modules needed by this dynamic library by using "
        "appropriate system utilities/ applications such as Microsoft's "
        "\"dependancy walker\" or \"FileAlyzer\"\n" ;
      break ;
    case ERROR_PROC_NOT_FOUND:
      strSol += "-If a DLL is compiled with a different version of a compiler
 	    " version than the executable that loads it and if this DLL has "
		"dependencies to other DLLs like [...]stdc++[...], [...]gcc_s[...] "
		"DLLs and these DLLs are available from another compiler version then"
        " this may be the cause.\n"
		"So ensure that the DLLs needed by a DLL are appropriate."
      break;
    }
#endif
#endif //#ifdef _WIN32
    return strSol ;
  }
} ;
