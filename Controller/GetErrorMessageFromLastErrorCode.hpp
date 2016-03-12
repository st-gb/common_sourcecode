/*
 * GetErrorMessageFromLastErrorCode.h
 *
 *  Created on: Sep 9, 2010
 *      Author: Stefan
 */

#ifndef GETERRORMESSAGEFROMLASTERRORCODE_H_
#define GETERRORMESSAGEFROMLASTERRORCODE_H_

#include <string> //class std::string
typedef unsigned long DWORD;

#ifdef __unix__
  #define Operating_Sytem Linux
#endif

//Implementation/ definition of these functions should be in a file in the
//appropriate folder ("Windows" / "Linux" ).
namespace Operating_Sytem
{
std::string GetErrorMessageFromLastErrorCodeA() ;
std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode) ;
std::wstring GetErrorMessageFromErrorCodeW(DWORD dwErrorCode) ;
};
//#ifdef __unix__

#endif /* GETERRORMESSAGEFROMLASTERRORCODE_H_ */
