/** File:   GetErrorMessageFromErrorCodeA.h
 * Author: s.g.
 * Created on 12. September 2017, 22:08 */

#ifndef GETERRORMESSAGEFROMERRORCODEA_H
#define GETERRORMESSAGEFROMERRORCODEA_H

#include <string>

namespace OperatingSystem
{
std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode) ;
std::wstring GetErrorMessageFromErrorCodeW(DWORD dwErrorCode) ;
}
//#ifdef 
//std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode )
//{
//  return ::LocalLanguageMessageAndErrorCodeA( dwErrorCode ) ;
//}

#endif /* GETERRORMESSAGEFROMERRORCODEA_H */

