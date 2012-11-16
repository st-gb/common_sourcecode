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

//#include <Controller/time/GetTimeAsMillisecondsValue.h>
#include <Controller/time/GetTickCount.hpp> //DWORD ::GetTickCount()

#include <preprocessor_macros/value_difference.h> //ULONG_VALUE_DIFF
#include "ReadTimeStampCounter.h" //ReadTSCinOrder(...)
#include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
#include <preprocessor_macros/show_via_GUI.h> //SHOW_VIA_GUI(...)
#include <tchar.h>
#include <inttypes.h> //uint64_t under Linux
//http://en.wikipedia.org/wiki/C_data_types
#include <float.h> //LDBL_MAX

//inline void GetCurrentReferenceClock(float fDivisor) ;

inline DWORD GetTimeCountInMilliseconds()
{
  return
    //Cites from:
    //http://msdn.microsoft.com/en-us/library/ms724408%28VS.85%29.aspx:
    //"The return value is the number of milliseconds that have elapsed since
    // the system was started."
    ::GetTickCount() ;
}

inline DWORD GetTickCountDiffInMilliseconds(
  DWORD s_dwTickCountInMilliseconds,
  DWORD s_dwPreviousTickCountInMilliseconds
  )
{
  return
    //Use this macro in order to take a value wrap into account:
    //http://msdn.microsoft.com/en-us/library/ms724408%28VS.85%29.aspx:
    // "[...]the time will wrap around to zero if the system is run
    //  continuously for 49.7 days"
    ULONG_VALUE_DIFF( s_dwTickCountInMilliseconds,
      s_dwPreviousTickCountInMilliseconds) ;
}

inline uint64_t GetTickCountDiffInNanoSeconds(
  uint64_t s_TimeCountInNanoSeconds,
  uint64_t s_PreviousTimeCountInNanoSeconds
  )
{
  return
    ULONGLONG_VALUE_DIFF( s_TimeCountInNanoSeconds,
      s_PreviousTimeCountInNanoSeconds) ;
}

inline void CalculateReferenceClockInMHzFromDiffs(
  unsigned long long int s_ullTimeStampCounterDiff,
  float fDivisor,
  float & r_fReferenceClockInMHz,
//  DWORD s_dwTickCountDiffInMilliseconds
//  uint64_t s_TimeCountDiffInNanoSeconds
  long double s_TimeCountDiffInNanoSeconds
  )
{
//    s_fReferenceClockInHertz = 1000.0 / (float) s_dwTickCountDiffInMilliseconds *
//(double) s_ullTimeStampCounterDiff /
//        fDivisor ;

//    s_fReferenceClockInHertz = 1000.0 *
//      (float) s_ullTimeStampCounterDiff /
//      fDivisor / (float) s_dwTickCountDiffInMilliseconds ;
////    g_fReferenceClockInMHz = s_fReferenceClockInHertz / 1000000.0 ;
//    r_fReferenceClockInMHz = s_fReferenceClockInHertz / 1000000.0 ;

//  static float fTimeStampsPerMillisecond;
//  fTimeStampsPerMillisecond = (float) s_ullTimeStampCounterDiff /
//    (float) s_dwTickCountDiffInMilliseconds;

  static float fTimeStampsPerNanoSecond;
  fTimeStampsPerNanoSecond = (double) s_ullTimeStampCounterDiff /
    (double) s_TimeCountDiffInNanoSeconds;
  DEBUGN( FULL_FUNC_NAME << "Time stamps/ nanosecond: "
    << fTimeStampsPerNanoSecond << "=" << s_ullTimeStampCounterDiff << "/"
    << s_TimeCountDiffInNanoSeconds)

  //TSC_diff/ms -> f[MHz] :   f=1/s   TSC_diff/ms = TSC_diff/0.0001s ->
  // TSC_diff * 1000 / 0.0001 * 1000.0 s = TSC_diff * 1000/s = TSC_diff * 1000 Hz
  // -> MHz: "f / 1000 000"
  r_fReferenceClockInMHz = //(float) s_ullTimeStampCounterDiff / fDivisor /
  //      //Get ratio of time span in which the TSC diff was measured and
  //      ( (float) s_dwTickCountDiffInMilliseconds / 1000.0f )
  //      / 1000000.0;
//    fTimeStampsPerMillisecond / fDivisor
//    //Divide TSCdiff/ms by 1000 to get f in MegaHertz
//    / 1000.0f;
    fTimeStampsPerNanoSecond / fDivisor;

  //    return s_fReferenceClockInHertz / 1000000.0 ;
  //    fReferenceClockInMHz = s_fReferenceClockInHertz / 1000000.0 ;
}

inline void GreaterMaxTimeDiff()
{
  //A bad idea follows because it blocks the execution.
//    //Wait some milliseconds to get a time difference.
//    ::Sleep(//500
//      dwMinimumTimeDiffInMilliseconds ) ;
//    s_dwTickCountInMilliseconds = ::GetTickCount();
//    s_dwTickCountDiffInMilliseconds =
////      //Use this macro in order to take a value wrap into account.
////      ULONG_VALUE_DIFF( s_dwTickCountInMilliseconds,
////      s_dwPreviousTickCountInMilliseconds) ;#
//        dwMinimumTimeDiffInMilliseconds ;

//    //overflows the same way as for GetTickCount() ;
//    s_dwTickCountInMilliseconds += dwMinimumTimeDiffInMilliseconds ;
}

//inline: do not compile as function, but expand code for every call (->faster)
//_Define_ the function in this _header_ file. It cannot be inline if declared
// in a header file and implemented in a source file if used in another file.
inline
  void
  //float
  GetCurrentReferenceClock(
    float fDivisor
    , float & r_fReferenceClockInMHz
    , DWORD dwMinimumTimeDiffInMilliseconds
    , DWORD dwMaximumTimeDiffInMilliseconds
//    , DWORD dwThreadAffinityMask
  )
{
//  static float s_fReferenceClockInHertz ;
  //float g_fReferenceClockInMHz ;
  static unsigned long long int s_ullPreviousTimeStampCounter ;
  static unsigned long long int s_ullCurrentTimeStampCounter ;
  static unsigned long long int s_ullTimeStampCounterDiff = _UI64_MAX ;

//  static DWORD s_dwPreviousTickCountInMilliseconds ;
//  static DWORD s_dwTickCountInMilliseconds ;
//  static DWORD s_dwTickCountDiffInMilliseconds;

  //http://en.wikipedia.org/wiki/C_data_types
  static long double s_PreviousTimeCountInSeconds = LDBL_MAX;
  static long double s_TimeCountInSeconds;
  static long double s_TimeCountDiffInSeconds;

//  static float g_fReferenceClockInMHz ;
//  SHOW_VIA_GUI( _T("GetCurrentReferenceClock begin") )

  //TODO need to execute getting time diff and TSC diff in the _same_ time slice.
  //Else between these two calculations a delay of some millisec. may occur that
  //falsifies the calculation.

//  s_dwTickCountInMilliseconds = GetTimeCountInMilliseconds();

  GetTimeCountInSeconds(s_TimeCountInSeconds);
//  s_ullPreviousTimeStampCounter = //ReadTimeStampCounter() ;
//    ReadTSCinOrder(
//      //pass thread affinity mask
//      1 //        dwThreadAffinityMask
//      ) ;

  DEBUGN( FULL_FUNC_NAME << "--TimeCountInSeconds:"
    << s_TimeCountInSeconds )

  if( s_PreviousTimeCountInSeconds == LDBL_MAX)
  {
    DEBUGN( FULL_FUNC_NAME << "--s_PreviousTimeCountInSeconds == LDBL_MAX" )
    s_PreviousTimeCountInSeconds = s_TimeCountInSeconds;
  }
  else
  {
  //  s_dwTickCountDiffInMilliseconds = GetTickCountDiffInMilliseconds(
  //    s_dwTickCountInMilliseconds,
  //    s_dwPreviousTickCountInMilliseconds);
    s_TimeCountDiffInSeconds = //GetTickCountDiffInNanoSeconds(
      //s_TimeCountInSeconds,
      //s_PreviousTimeCountInSeconds);
      s_TimeCountInSeconds - s_PreviousTimeCountInSeconds;

    DEBUGN( FULL_FUNC_NAME << "--tick count diff in s: "
      << //s_dwTickCountDiffInMilliseconds
      s_TimeCountDiffInSeconds)
    if(
        //If at the beginning / for the first time.
  //      s_dwTickCountInMilliseconds == ULONG_MAX
  //      s_dwTickCountDiffInMilliseconds //== 0
  //      < dwMinimumTimeDiffInMilliseconds

  //      s_dwTickCountDiffInMilliseconds > dwMaximumTimeDiffInMilliseconds
  //      s_TimeCountDiffInNanoSeconds > dwMaximumTimeDiffInMilliseconds * 1000
        s_TimeCountDiffInSeconds * 1000.0 > dwMaximumTimeDiffInMilliseconds
      )
    {
      DEBUGN( FULL_FUNC_NAME << "--tick count diff > MAX time diff")
  //    s_dwPreviousTickCountInMilliseconds = s_dwTickCountInMilliseconds ;
      //s_PreviousTimeCountInNanoSeconds = s_TimeCountInNanoSeconds;
      s_PreviousTimeCountInSeconds = s_TimeCountInSeconds;

      //Because the time difference is  too large:take a TSC measurement (again).
      s_ullPreviousTimeStampCounter = //ReadTimeStampCounter() ;
        ReadTSCinOrder(
          //pass thread affinity mask
          1 //        dwThreadAffinityMask
          ) ;

  //    GreaterMaxTimeDiff();

      //Set to 0 for the following comparison ">="
  //    s_dwTickCountDiffInMilliseconds = 0 ;
  //    s_TimeCountDiffInNanoSeconds = 0;
      s_TimeCountDiffInSeconds = 0;
    }
  //  //Use global var., so it does not need to be created on stack for every time.
  //  s_dwTickCountInMilliseconds = ::GetTickCount() ;
  //  s_dwTickCountDiffInMilliseconds =
  //    //Use this macro in order to take a value wrap into account.
  //    ULONG_VALUE_DIFF( s_dwTickCountInMilliseconds,
  //    s_dwPreviousTickCountInMilliseconds) ;

  //  SHOW_VIA_GUI( _T("GetCurrentReferenceClock before tick count comp") )
    //If getcurrentpstate for core 0 and directly afterwards for core 1,
    //s_dwTickCountDiffInMilliseconds may be too small->too inexact,
    //if s_dwTickCountDiffInMilliseconds=0: division by zero.

    if( //s_dwTickCountDiffInMilliseconds >= dwMinimumTimeDiffInMilliseconds
  //      s_TimeCountDiffInNanoSeconds >= dwMinimumTimeDiffInMilliseconds * 1000
        s_TimeCountDiffInSeconds * 1000.0 > dwMinimumTimeDiffInMilliseconds
      )
    {
      DEBUGN( FULL_FUNC_NAME << "--tick count diff > MIN time diff")
  //    SHOW_VIA_GUI( _T("GetCurrentReferenceClock s_dwTickCountDiffInMilliseconds"
  //      " >=dwMinimumTimeDiffInMilliseconds") )
  //    DEBUGN( FULL_FUNC_NAME << "GetCurrentReferenceClock(...)"
  //      "--tick count diff ("
  //      << s_dwTickCountDiffInMilliseconds << ") > min time span("
  //      << dwMinimumTimeDiffInMilliseconds << ")" )

  //    s_dwPreviousTickCountInMilliseconds = s_dwTickCountInMilliseconds ;
  //    s_PreviousTimeCountInNanoSeconds = s_TimeCountInNanoSeconds;
      s_PreviousTimeCountInSeconds = s_TimeCountInSeconds;

  //      std::stringstream stdstrstream ;
    //  stdstrstream << s_dwTickCountDiffInMilliseconds ;
    //  MessageBox(NULL, stdstrstream.str().c_str() , "info" , MB_OK) ;

  //    SHOW_VIA_GUI( _T("GetCurrentReferenceClock before ReadTSCinOrder") )

      s_ullCurrentTimeStampCounter = //ReadTimeStampCounter() ;
        ReadTSCinOrder(//pass thread affinity mask
          1) ;
  //    SHOW_VIA_GUI( _T("GetCurrentReferenceClock after ReadTSCinOrder") )

      s_ullTimeStampCounterDiff = ULONGLONG_VALUE_DIFF(
        s_ullCurrentTimeStampCounter , s_ullPreviousTimeStampCounter ) ;

      DEBUGN( FULL_FUNC_NAME << "TSC diff: " << s_ullTimeStampCounterDiff )

      s_ullPreviousTimeStampCounter = s_ullCurrentTimeStampCounter ;

    //  stdstrstream << s_ullTimeStampCounterDiff ;
    //  MessageBox(NULL, stdstrstream.str().c_str() , "info" , MB_OK) ;

      CalculateReferenceClockInMHzFromDiffs(
        s_ullTimeStampCounterDiff,
        fDivisor,
        r_fReferenceClockInMHz,
  //      s_TimeCountDiffInNanoSeconds
        //(uint64_t)
        (s_TimeCountDiffInSeconds * 1000000.0)
        );

    //  stdstrstream << fReferenceClockInMHz ;
    //  MessageBox(NULL, stdstrstream.str().c_str() , "info" , MB_OK) ;
    }
    else
    {
  //    SHOW_VIA_GUI(_T("GetCurrentReferenceClock setting ref clock to 0") )
      SHOW_VIA_GUI( _T("GetCurrentReferenceClock BEFORE setting ref clock to 0") )
      r_fReferenceClockInMHz = 0.0f ;
      SHOW_VIA_GUI( _T("GetCurrentReferenceClock AFTER setting ref clock to 0") )
    }
  }
  DEBUGN( FULL_FUNC_NAME << "--end")
}

#endif /* GETCURRENTREFERENCECLOCK_HPP_ */
