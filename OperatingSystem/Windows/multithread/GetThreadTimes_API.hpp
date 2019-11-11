/*
 * GetThreadTimes_API.hpp
 *
 *  Created on: 22.06.2013
 *      Author: Stefan
 */

#ifndef GETTHREADTIMES_API_HPP_
#define GETTHREADTIMES_API_HPP_

#include <windows.h> //::GetThreadTimes(...)

  namespace GetThreadTimesAPI
  {
    bool GetTimeExecuted(
      const HANDLE & hThread,
      ULONG64 & ul64_100NsIntervalsExecutedInUserMode,
      ULONG64 & ul64_100NsIntervalsExecutedInKernelMode)
    {
//      ULONG64 ul64_100NsIntervalsExecutedInUserMode = 0ULL;
      static FILETIME creationTime;
      static FILETIME exitTime;
      static FILETIME kernelTime;
      static FILETIME timeExecutedInUserMode;

#if __INT_MAX__==2147483647  // 32 bit compiler
      //from http://stackoverflow.com/questions/1393006/how-to-get-the-cpu-usage-per-thread-on-windows-win32
      //maybe see
      //-http://www.tech-archive.net/Archive/Development/microsoft.public.win32.programmer.kernel/2004-10/0689.html
      //-http://blog.kalmbachnet.de/?postid=28 ("Why GetThreadTimes is wrong")
      //-http://groups.google.de/groups?th=4b1324af593749b
      bool b = GetThreadTimes(
          hThread, //_In_   HANDLE hThread,
          & creationTime, //_Out_  LPFILETIME lpCreationTime,
          & exitTime, // _Out_  LPFILETIME lpExitTime,
          & kernelTime, // _Out_  LPFILETIME lpKernelTime,
          & timeExecutedInUserMode // _Out_  LPFILETIME lpUserTime);
          );
#else
      bool b = GetThreadTimes(
          hThread, //_In_   HANDLE hThread,
          & creationTime, //_Out_  LPFILETIME lpCreationTime,
          & exitTime, // _Out_  LPFILETIME lpExitTime,
          //& kernelTime, // _Out_  LPFILETIME lpKernelTime,
          & ul64_100NsIntervalsExecutedInKernelMode,
          & timeExecutedInUserMode // _Out_  LPFILETIME lpUserTime);
          );
#endif
      if( b)
      {
        //ul64_100NsIntervalsExecutedInUserMode = (ULONG64) timeExecutedInUserMode;

        //msdn.microsoft.com/en-us/library/windows/desktop/ms724284(v=vs.85).aspx:
        //"It is not recommended that you add and subtract values from the
        // FILETIME structure to obtain relative times. Instead, you should
        //copy the low- and high-order parts of the file time to a
        //ULARGE_INTEGER structure, perform 64-bit arithmetic on the QuadPart
        //member, and copy the LowPart and HighPart members into the FILETIME
        //structure."
        //"Do not cast a pointer to a FILETIME structure to either a
        // ULARGE_INTEGER* or __int64* value because it can cause alignment
        //faults on 64-bit Windows."
        ul64_100NsIntervalsExecutedInUserMode = timeExecutedInUserMode.dwHighDateTime;
        ul64_100NsIntervalsExecutedInUserMode <<= 32;
        ul64_100NsIntervalsExecutedInUserMode |= timeExecutedInUserMode.dwLowDateTime;

        ul64_100NsIntervalsExecutedInKernelMode = kernelTime.dwHighDateTime;
        ul64_100NsIntervalsExecutedInKernelMode <<= 32;
        ul64_100NsIntervalsExecutedInKernelMode |= kernelTime.dwLowDateTime;
      }
//      else
//      {
//        LOGN_WARNING( " calling GetThreadTimes failed: "
//          << ::GetErrorMessageFromLastErrorCodeA() )
//      }
      return b;
    }
  }

#endif /* GETTHREADTIMES_API_HPP_ */
