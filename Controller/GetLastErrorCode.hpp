/*
 * GetLastErrorCode.h
 *
 *  Created on: Sep 17, 2010
 *      Author: sgebauer
 */

#ifndef GETLASTERRORCODE_H_
#define GETLASTERRORCODE_H_

namespace OperatingSystem
{
//  DWORD GetLastErrorCode() ;
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <Windows/ErrorCode/GetLastErrorCode.hpp>
#endif
#ifdef __linux__
  #include <Linux/GetLastErrorCode.hpp>
#endif
} ;

#endif /* GETLASTERRORCODE_H_ */
