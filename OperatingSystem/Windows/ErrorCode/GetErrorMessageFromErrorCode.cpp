#include <string> //class std::string
#include <windef.h> //DWORD
#include "LocalLanguageMessageFromErrorCode.h"

namespace OperatingSystem/*Windows_API*/
{
    std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode )
    {
      return ::LocalLanguageMessageAndErrorCodeA( dwErrorCode ) ;
    }
  //std::wstring GetErrorMessageFromErrorCodeW(DWORD dwErrorCode){
  //    return ::LocalLanguageMessageAndErrorCodeW( dwErrorCode ) ;
  //  }
}