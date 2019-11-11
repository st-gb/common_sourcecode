#include <string> //class std::string
#include <windef.h> //DWORD
#include <Windows/ErrorCode/LocalLanguageMessageFromErrorCode.h>

namespace OperatingSystem/*Windows_API*/
{
    std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode )
    {
      return ::LocalLanguageMessageAndErrorCodeA( dwErrorCode ) ;
    }
}