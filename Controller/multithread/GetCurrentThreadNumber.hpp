/*
 * GetCurrentThreadID.h
 *
 *  Created on: 10.02.2013
 *      Author: Stefan
 */

#ifndef GETCURRENTTHREADID_H_
#define GETCURRENTTHREADID_H_

#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  #include <windows.h> //::GetCurrentThreadId()
#endif
#ifdef __linux__
  #include <Linux/GetCurrentThreadNumber.h>
  using namespace Linux;
  #include "preprocessor_macros/Windows_compatible_typedefs.h" //for DWORD
//  #ifndef DWORD
//    #define DWORD unsigned
//  #endif
#endif

namespace OperatingSystem
{
#ifdef _WIN32 //Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
  inline DWORD GetCurrentThreadNumber() {
#ifdef _DEBUG
    DWORD dwCurrentThreadId = ::GetCurrentThreadId();
    return dwCurrentThreadId;
#else
    return ::GetCurrentThreadId();
#endif
  }
#endif
#ifdef __linux__
  inline DWORD GetCurrentThreadNumber() {
    return Linux::GetCurrentThreadNumber();
  }
#endif
};

#endif /* GETCURRENTTHREADID_H_ */
