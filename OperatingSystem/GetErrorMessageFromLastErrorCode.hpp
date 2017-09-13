/*
 * GetErrorMessageFromLastErrorCode.h
 *
 *  Created on: Sep 9, 2010
 *      Author: Stefan
 */

#ifndef GET_ERRORMESSAGEFROMLASTERRORCODE_H_
#define GET_ERRORMESSAGEFROMLASTERRORCODE_H_

#include <string> //class std::string
typedef unsigned long DWORD;

//#ifdef __unix__
//  #define Operating_Sytem Linux
//#endif
#ifdef _WIN32
  #define OperatingSytem Windows
#endif
//Implementation/ definition of these functions should be in a file in the
//appropriate folder ("Windows" / "Linux" ).
namespace OperatingSystem
{
std::string GetErrorMessageFromLastErrorCodeA() ;
};
//#ifdef __unix__

#endif /* GETERRORMESSAGEFROMLASTERRORCODE_H_ */
