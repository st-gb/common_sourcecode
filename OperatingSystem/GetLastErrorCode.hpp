/*
 * GetLastErrorCode.h
 *
 *  Created on: Sep 17, 2010
 *      Author: sgebauer
 */

#ifndef OPERATING_SYSTEM_GETLASTERRORCODE_H_
#define OPERATING_SYSTEM_GETLASTERRORCODE_H_

#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  //#define OperatingSystem Windows_API
  #include <OperatingSystem/Windows/ErrorCode/GetLastErrorCode.hpp>
#endif
#ifdef __linux__
  #include <OperatingSystem/Linux/GetLastErrorCode.hpp>
  //#define OperatingSystem Linux
#endif

//namespace OperatingSystem
//{
////  DWORD GetLastErrorCode() ;
//
//} ;

#endif /* OPERATING_SYSTEM_GETLASTERRORCODE_H_ */
