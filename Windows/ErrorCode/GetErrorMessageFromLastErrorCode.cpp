/*
 * GetErrorMessageFromLastErrorCode.cpp
 *
 *  Created on: Oct 26, 2010
 *      Author: Stefan
 */

#include <Windows/ErrorCode/LocalLanguageMessageFromErrorCode.h>
#include <windows.h> //WINBASEAPI DWORD WINAPI GetLastError(void);

std::string GetErrorMessageFromLastErrorCodeA()
{
  return LocalLanguageMessageAndErrorCodeA( ::GetLastError() ) ;
}
