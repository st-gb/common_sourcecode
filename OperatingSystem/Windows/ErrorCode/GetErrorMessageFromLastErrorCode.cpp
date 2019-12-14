/** GetErrorMessageFromLastErrorCode.cpp
 *  Created on: Oct 26, 2010
 *      Author: Stefan */

#include "LocalLanguageMessageFromErrorCode.h"
#include <windows.h> //WINBASEAPI DWORD WINAPI GetLastError(void);

namespace OperatingSystem //Windows_API/**/
{
std::string GetErrorMessageFromLastErrorCodeA()
{
  return ::LocalLanguageMessageAndErrorCodeA( ::GetLastError() ) ;
}
}