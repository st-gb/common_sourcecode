/* 
 * File:   Sleep.h
 * Author: Stefan
 *
 * Created on 14. November 2009, 03:40
 */

#ifndef _SLEEP_HPP
#define	_SLEEP_HPP

//necessary for name mangling for Windows API's "::Sleep(...)"
#ifdef	__cplusplus
extern "C" {
#endif

#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
//  #define SLEEP_1_MILLI_SECOND ::Sleep(1) ;
  //Compile problems like
//  "In file included from c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../
//  include/c++/3.4.5/bits/stl_algobase.h:67,
//     from c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/
//  3.4.5/bits/char_traits.h:46,
//     from c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/
//  3.4.5/ios:46,
//     from c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/
//  3.4.5/istream:45,
//     from c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/
//  3.4.5/fstream:45,
//     from T:/SourceCodeManagement/common_sourcecode/Controller/Logger/
//      Logger.hpp:4,
//     from T:/SourceCodeManagement/common_sourcecode/preprocessor_macros/
//      logging_preprocessor_macros.h:56,
//     from T:/SourceCodeManagement/X86Info_and_Control/Controller/CPU-related/
//      ICPUcoreUsageGetter.hpp:3,
//  from ..\..\..\..\X86Info_and_Control\Controller\CalculationThreadProc.cpp:9:
//  c:/mingw/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/3.4.5/
//    cstdlib:86: error: `::div_t' has not been declared
// [...]"
//  when including <windows.h>
//  #include <windows.h> //for Sleep(...);
  //As in declared <winbase.h>
  #define WINBASEAPI
  typedef unsigned long int DWORD ;
  #define WINAPI __stdcall
  WINBASEAPI void WINAPI Sleep(DWORD);
  #include <fastest_data_type.h> //
#endif //#ifdef _WIN32

#ifdef  __cplusplus
}
#endif

namespace OperatingSystem
{
#ifdef _WIN32 //Built-in macro for MSVC, MinGW (also for 64 bit Windows)
  inline void Sleep(/*unsigned long*/ fastestUnsignedDataType milliSeconds )
  {
    ::Sleep(milliSeconds) ;
//    Sleep(dwMilliSeconds) ;
  }
  inline void SleepMilliSeconds(fastestUnsignedDataType milliSeconds )
  {
    ::Sleep(milliSeconds) ;
//    Sleep(dwMilliSeconds) ;
  }
#else //#ifdef _WIN32
  #include <unistd.h>
  inline void Sleep(/*unsigned long*/ fastestUnsignedDataType milliSeconds )
  {
    usleep( 1000 * milliSeconds );
  }
  inline void SleepMilliSeconds(fastestUnsignedDataType milliSeconds )
  {
    //micro (10^-6 * 10^3 = *10^-3
    //1 millisecond = 1000 microseconds
    usleep( 1000 * milliSeconds );
  }
#endif //#ifdef _WIN32
}

#endif	/* _SLEEP_HPP */

