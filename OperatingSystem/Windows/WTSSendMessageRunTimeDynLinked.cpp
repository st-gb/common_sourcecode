/*
 * WTSSendMessageRunTimeDynLinked.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: Stefan
 */
//#include <global.h>
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <windows.h> //::GetProcAddress()
#include <tchar.h> //for _T()
#include <Windows/LocalLanguageMessageFromErrorCode.h>
//When this include file was included before the (indirect) inclusion of
// bits/c++locale.h then g++ error:
//..\..\..\..\common_sourcecode\Windows\WTSSendMessageRunTimeDynLinked.cpp:10:
//c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/3.4.5/mingw32/
//  bits/c++locale.h:
//  In function `int std::__convert_from_v(char*, int, const char*, _Tv,
//  int* const&, int)':
// c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/3.4.5/
//  mingw32/bits/c++locale.h:73: error: expected primary-expression before ','
//  token
#include "WTSSendMessageRunTimeDynLinked.hpp"

//from http://msdn.microsoft.com/en-us/library/aa383842%28VS.85%29.aspx:
BOOL WTSSendMessage(
  //__in (specstrings.h is not available on every MinGW installation)
		HANDLE hServer,
  //__in (specstrings.h is not available on every MinGW installation)
		DWORD SessionId,
  //__in (specstrings.h is not available on every MinGW installation)
		LPTSTR pTitle,
  //__in (specstrings.h is not available on every MinGW installation)
		DWORD TitleLength,
  //__in (specstrings.h is not available on every MinGW installation)
		LPTSTR pMessage,
  //__in (specstrings.h is not available on every MinGW installation)
		DWORD MessageLength,
  //__in (specstrings.h is not available on every MinGW installation)
		DWORD Style,
  //__in (specstrings.h is not available on every MinGW installation)
		DWORD Timeout,
  //__out (specstrings.h is not available on every MinGW installation)
		DWORD *pResponse,
  //__in (specstrings.h is not available on every MinGW installation)
		BOOL bWait
)
{
  HMODULE handleWtsapi32DLL = ::LoadLibrary( _T("Wtsapi32.dll") );
  if ( handleWtsapi32DLL )
  {
    LOGN( "got handle to Wtsapi32.dll" )
#ifdef UNICODE
    char arch [] = "WTSSendMessageW" ;
#else
    char arch [] = "WTSSendMessageA" ;
#endif
    pfnWTSSendMessage pfn_wtssendmessage = (pfnWTSSendMessage)
    ::GetProcAddress( handleWtsapi32DLL, arch );
    if( pfn_wtssendmessage )
    {
      LOGN( "got pointer to " << arch)
      //TODO WTSSendMessage fails with error code 5 (access denied)
      //Cites from
      //http://msdn.microsoft.com/en-us/library/aa383842%28VS.85%29.aspx:
      BOOL bool_ =
        //"If the function succeeds, the return value is a nonzero value."
        (*pfn_wtssendmessage) (
        hServer,
        SessionId,
        pTitle,
        TitleLength,
        pMessage,
        MessageLength,
        Style,
        Timeout,
        pResponse,
        bWait
        ) ;
      //"If the function fails, the return value is zero. To get extended
      //error information, call GetLastError."
      if( ! bool_ )
        LOGN("calling " << arch << " failed: " <<
          LocalLanguageMessageAndErrorCodeA(::GetLastError() ) )
      LOGN( "ret of " << arch << ":" << bool_ << " " << *pResponse )
    }
    ::FreeLibrary( handleWtsapi32DLL );
  }
  return FALSE ;
}
