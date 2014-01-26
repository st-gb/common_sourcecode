/*
 * GetLastErrorCode.h
 *
 *  Created on: Sep 17, 2010
 *      Author: sgebauer
 */

#ifndef GETLASTERRORCODE_H_
#define GETLASTERRORCODE_H_

#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #define OperatingSystem Windows
  #include <Windows/ErrorCode/GetLastErrorCode.hpp>
#endif
#ifdef __linux__
  #define OperatingSystem Linux
  #include <Linux/GetLastErrorCode.hpp>
#endif

//namespace OperatingSystem
//{
////  DWORD GetLastErrorCode() ;
//
//} ;

#endif /* GETLASTERRORCODE_H_ */
