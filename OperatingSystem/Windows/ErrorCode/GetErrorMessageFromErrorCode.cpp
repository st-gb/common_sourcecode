///@author Stefan Gebauer(TU Berlin matriculation number 361095)

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

///Stefan Gebauer's(TU Berlin mat.#361095)~"common_sourcecode" repository files:
#include "LocalLanguageMessageFromErrorCode.h"

namespace OperatingSystem/*Windows_API*/
{
	///"A"=ASCII character string version
    std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode )
    {
      return ::LocalLanguageMessageAndErrorCodeA( dwErrorCode ) ;
    }
  //std::wstring GetErrorMessageFromErrorCodeW(DWORD dwErrorCode){
  //    return ::LocalLanguageMessageAndErrorCodeW( dwErrorCode ) ;
  //  }
}