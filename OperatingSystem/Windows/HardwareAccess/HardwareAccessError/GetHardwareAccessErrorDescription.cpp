/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * GetHardwareAccessErrorDescription.cpp
 *
 *  Created on: Jun 26, 2010
 *      Author: Stefan
 */
#include "GetHardwareAccessErrorDescription.hpp"
//for convertToStdString(...)
#include <Controller/character_string/stdstring_format.hpp>
//#include <Windows/ErrorCodeFromGetLastErrorToString.h>
#include <OperatingSystem/Windows/ErrorCode/LocalLanguageMessageFromErrorCode.h>
#include <winerror.h> //for ERROR_GEN_FAILURE

//Gets the description for PCconfig , IO , MSR etc. access
//May be used if different hardware accesses (WinRing0 versions, ...) fail.
std::string GetHardwareAccessErrorDescription(
  DWORD dwErrorCode,
  const //std::string &
  char * stdstrHardwareType ,
  DWORD dwIndex
  )
{
  std::string strErrorMessage ;
  //::GetLastErrorMessageString(
//    dwErrorCode ,
//    strErrorMessage
//    ) ;
    strErrorMessage = ::LocalLanguageMessageAndErrorCodeA(dwErrorCode) ;
//  std::string stdstrAdditionalInfo = "" ;
  switch(dwErrorCode)
  {
  case ERROR_GEN_FAILURE:
    strErrorMessage += "\nThis error code could mean that " +
    std::string(stdstrHardwareType) + " address \""
      + convertToStdString<DWORD>(dwIndex) + "\" is not available/ accessible "
      //"on the CPU"
      ;
      break ;
  }
  return strErrorMessage ;
}
