/*
 * GetCurrentReferenceClock.hpp
 *
 *  Created on: Jun 4, 2010
 *      Author: Stefan
 */
//This file is intellectual property of Trilobyte SE GmbH, Berlin, Germany.
//Copyright 2010 by Trilobyte SE GmbH, Berlin, Germany.
//It must not be used commercially without the permission of Trilobyte
//SE GmbH, Berlin, Germany.
//It may be used for educational / academic purposes for free.
//If you use (parts) of this sourcecode then this license text must be contained.
#ifndef GETCURRENTREFERENCECLOCK_HPP_
#define GETCURRENTREFERENCECLOCK_HPP_

#include <windows.h> // GetTickCount()
#include <preprocessor_macros/value_difference.h> //ULONG_VALUE_DIFF
#include "ReadTimeStampCounter.h"
//#include <global.h>
#include <preprocessor_macros/logging_preprocessor_macros.h>

//inline void GetCurrentReferenceClock(float fDivisor) ;

//TODO put variable definitions into a source file (that is not #included)
// to avoid multiple definitions.
//Declare and use global variables to be faster (using local variables creates
//them on stack each time).
float g_fReferenceClockInHertz ;
//float g_fReferenceClockInMHz ;
extern float g_fReferenceClockInMHz ;
unsigned long long int g_ullPreviousTimeStampCounter ;
unsigned long long int g_ullCurrentTimeStampCounter ;
unsigned long long int g_ullTimeStampCounterDiff = _UI64_MAX ;
DWORD g_dwPreviousTickCountInMilliseconds ;
DWORD g_dwTickCountInMilliseconds ;
DWORD g_dwTickCountDiffInMilliseconds = //ULONG_MAX ;
    0 ;

//inline: do not compile as function, but expand code for every call (->faster)
//Define the function in this _header_ file. It cannot be inline if declared in
// a header file and implemented in a source file?!
inline
  void
  //float
  GetCurrentReferenceClock( float fDivisor
  , float & r_fReferenceClockInMHz
  , DWORD dwMinimumTimeDiffInMilliseconds
  , DWORD dwMaximumTimeDiffInMilliseconds
  )
{
  //Use global var., so it does not need to be created on stack for every time.
  g_dwTickCountInMilliseconds =
    //Cites from:
    //http://msdn.microsoft.com/en-us/library/ms724408%28VS.85%29.aspx:
    //"The return value is the number of milliseconds that have elapsed since
    // the system was started."
    ::GetTickCount() ;
  g_dwTickCountDiffInMilliseconds =
    //Use this macro in order to take a value wrap into account:
    //http://msdn.microsoft.com/en-us/library/ms724408%28VS.85%29.aspx:
    // "[...]the time will wrap around to zero if the system is run
    //  continuously for 49.7 days"
    ULONG_VALUE_DIFF( g_dwTickCountInMilliseconds,
    g_dwPreviousTickCountInMilliseconds) ;
  DEBUGN("tick count diff in ms: " << g_dwTickCountDiffInMilliseconds )
  if( //g_ullTimeStampCounterDiff == _UI64_MAX // ^= "= 0"
      //If at the beginning / for the first time.
//      g_dwTickCountInMilliseconds == ULONG_MAX
//      g_dwTickCountDiffInMilliseconds //== 0
//      < dwMinimumTimeDiffInMilliseconds
//      ||
      g_dwTickCountDiffInMilliseconds > dwMaximumTimeDiffInMilliseconds
    )
  {
    g_dwPreviousTickCountInMilliseconds = g_dwTickCountInMilliseconds ;
    //Because the time difference is  too large:take a TSC measurement (again).
    g_ullPreviousTimeStampCounter = //ReadTimeStampCounter() ;
      ReadTSCinOrder(
        //pass thread affinity mask
        1) ;
    //A bad idea follows because it blocks the execution.
//    //Wait some milliseconds to get a time difference.
//    ::Sleep(//500
//      dwMinimumTimeDiffInMilliseconds ) ;
//    g_dwTickCountInMilliseconds = ::GetTickCount();
//    g_dwTickCountDiffInMilliseconds =
////      //Use this macro in order to take a value wrap into account.
////      ULONG_VALUE_DIFF( g_dwTickCountInMilliseconds,
////      g_dwPreviousTickCountInMilliseconds) ;#
//        dwMinimumTimeDiffInMilliseconds ;

//    //overflows the same way as for GetTickCount() ;
//    g_dwTickCountInMilliseconds += dwMinimumTimeDiffInMilliseconds ;

    //Set to 0 for the following comparison ">="
    g_dwTickCountDiffInMilliseconds = 0 ;
  }
//  //Use global var., so it does not need to be created on stack for every time.
//  g_dwTickCountInMilliseconds = ::GetTickCount() ;
//  g_dwTickCountDiffInMilliseconds =
//    //Use this macro in order to take a value wrap into account.
//    ULONG_VALUE_DIFF( g_dwTickCountInMilliseconds,
//    g_dwPreviousTickCountInMilliseconds) ;

  //If getcurrentpstate for core 0 and directly afterwards for core 1,
  //g_dwTickCountDiffInMilliseconds may be too small->too inexact,
  //if g_dwTickCountDiffInMilliseconds=0: division by zero.
  if( g_dwTickCountDiffInMilliseconds >= //1000
    dwMinimumTimeDiffInMilliseconds )
  {
    DEBUGN("GetCurrentReferenceClock(...) tick count diff ("
      << g_dwTickCountDiffInMilliseconds << ") > min time span("
      << dwMinimumTimeDiffInMilliseconds << ")" )
    g_dwPreviousTickCountInMilliseconds = g_dwTickCountInMilliseconds ;
//      std::stringstream stdstrstream ;
  //  stdstrstream << g_dwTickCountDiffInMilliseconds ;
  //  MessageBox(NULL, stdstrstream.str().c_str() , "info" , MB_OK) ;

    g_ullCurrentTimeStampCounter = //ReadTimeStampCounter() ;
      ReadTSCinOrder(//pass thread affinity mask
        1) ;
    g_ullTimeStampCounterDiff = ULONGLONG_VALUE_DIFF(
      g_ullCurrentTimeStampCounter , g_ullPreviousTimeStampCounter ) ;
    DEBUGN("TSC diff: " << g_ullTimeStampCounterDiff )
    g_ullPreviousTimeStampCounter = g_ullCurrentTimeStampCounter ;
  //  stdstrstream << g_ullTimeStampCounterDiff ;
  //  MessageBox(NULL, stdstrstream.str().c_str() , "info" , MB_OK) ;

//    g_fReferenceClockInHertz = 1000.0 / (float) g_dwTickCountDiffInMilliseconds *
    //(double) g_ullTimeStampCounterDiff /
//        fDivisor ;
    g_fReferenceClockInHertz = 1000.0 *
      (double) g_ullTimeStampCounterDiff /
      fDivisor / (float) g_dwTickCountDiffInMilliseconds ;
//    g_fReferenceClockInMHz = g_fReferenceClockInHertz / 1000000.0 ;
    r_fReferenceClockInMHz =  g_fReferenceClockInHertz / 1000000.0 ;
//    return g_fReferenceClockInHertz / 1000000.0 ;
//    fReferenceClockInMHz = g_fReferenceClockInHertz / 1000000.0 ;
  //  stdstrstream << fReferenceClockInMHz ;
  //  MessageBox(NULL, stdstrstream.str().c_str() , "info" , MB_OK) ;
  }
  else
    r_fReferenceClockInMHz = 0.0 ;
}

#endif /* GETCURRENTREFERENCECLOCK_HPP_ */