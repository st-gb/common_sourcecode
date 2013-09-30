#ifndef GET_CPU_CLOCK_VIA_TSC_DIFF
#define GET_CPU_CLOCK_VIA_TSC_DIFF

/** This code was adapted from CrystalCPUID version 4.154452's sourcecode of the
 * Real Time Clock dialog (<<source root directory>>\RealTimeClockDlg.cpp). */
// Original copyright:
/*---------------------------------------------------------------------------*/
//       Author : hiyohiyo
//         Mail : hiyohiyo@crystalmark.info
//          Web : http://crystalmark.info/
//      License : The modified BSD license
//
//                           Copyright 2002-2005 hiyohiyo, All rights reserved.
/*---------------------------------------------------------------------------*/

#include <windows.h>
#include <windef.h>
#include <Controller/CPU-related/ReadTimeStampCounter.h>
#include <fastest_data_type.h>

//static float error;
//Ensure no other process etc. was executed between QueryPeformanceCounter and rdtsc.
//  -0.0001 s are needed when outputting into log files?
//  -else 0.00001 s?
#define MIN_TIME_SPAN_IN_S 0.0001f

namespace CPU
{
  /***/
  inline void PossiblyGiveTimeSliceToOtherProcesses()
  {
    //Use "::Sleep(0)" under Windows to let another process get CPU time
    //  so that less CPU time is wasted.
    //http://msdn.microsoft.com/en-us/library/windows/desktop/ms686298%28v=vs.85%29.aspx
    //"A value of zero causes the thread to relinquish the remainder of its
    //time slice to any other thread that is ready to run. If there are no
    //other threads ready to run, the function returns immediately, and the
    //thread continues execution.
    //Windows XP:  A value of zero causes the thread to relinquish the
    //remainder of its time slice to any other thread of equal priority that
    //is ready to run. If there are no other threads of equal priority ready
    //to run, the function returns immediately, and the thread continues
    //execution. This behavior changed starting with Windows Server 2003."

    //->under WinXP only when there is a thread with _equal_ priority the
    //rest of CPU time is given to ob.
    ::Sleep(0);
    DEBUGN("after calling Sleep(0)")
  }

  namespace OneLogicalCore
  {
    inline void GetClockWithLoad()
    {
    }
  }

  inline void ReadTSC(
    LARGE_INTEGER * p_liBeforeReadTSC,
    LARGE_INTEGER * p_liAfterReadTSC,
    ULARGE_INTEGER & uliTimeStampCounterValue)
  {
    ::QueryPerformanceCounter( p_liBeforeReadTSC);
    uliTimeStampCounterValue.QuadPart = //ReadTSCinOrder(/*&StartL,&StartH*/ affMask);
#ifdef READTSC_IS_EXECUTED_IN_ORDER
      ReadTimeStampCounter();
#else //the "rdtsc" instruction is executed out of order
      ReadTSCinOrderFromEnglishWikipedia();
#endif
    ::QueryPerformanceCounter( p_liAfterReadTSC);
  }

  /** @brief gets CPU core via busy waiting (-> no non-C0/ sleep/ halt states
   *   where the TSC may not increment (e.g. Intel Pentium M stepping 10,
   *   Intel Core 2 Celeron 900)
   *   GetVoltageAndMultiplier(...) must be declared before.
   *
   * @param multiplier: the multiplier that is read between TSC start and end
   * @param numMinimumSteps:
   *   in: determines the error %
   *   -constant TSC (Core 2): set to min. ~ 100: error % ~= 1/100
   *    -> when 2GHz CPU clock calculated then it actually may be +- 2 MHz
   *   -variable TSC (Pentium M): it should be around 20
   *    to get a tradeoff between inaccuracy when the TSC changes and the error
   *    %
   *   out: number of timer steps elapsed: error %
   * @param waitTimeInSeconds: time after which the TSC diff loop breaks
   *   -constant TSC (Core 2): set to min. ~ 100: error % ~= 1/100
   *    -> when 2GHz CPU clock calculated then it actually may be +- 2 MHz
   *   -variable TSC (Pentium M): it should be around 0.00001 s
   *    to get a tradeoff between inaccuracy when the TSC changes and the error
   * @return CPUcore frequency in MHz*/
  inline double GetClockWithLoad(
    DWORD affMask,
    float & multiplier,
    fastestUnsignedDataType & numMinimumSteps,
    float & waitTimeInSeconds,
    float & r_fVoltageInVolt)
  {
    static ULARGE_INTEGER lTimeStampCounterBefore, lTimeStampCounterAfter, 
      numTSCticksElapsed;
    static LARGE_INTEGER lStartPerfCounterValue, lPerfCounterValueBeforeStart,
	    timerStepsPassed, lPerfCounterValueBeforeEnd, lEndPerfCounterValue,
	  lPerfCounterStepsPerSecond;

    double clock = -1.0;

    DWORD mask;

    QueryPerformanceFrequency(&lPerfCounterStepsPerSecond);
    DEBUGN( "numMinimumSteps:" << numMinimumSteps
      << " waitTimeInSeconds:" << waitTimeInSeconds
      << " timer ticks/s:" << lPerfCounterStepsPerSecond.QuadPart )
    double secondsPerTimerTick = 1.0 / (double) lPerfCounterStepsPerSecond.QuadPart;

    //Set thread affinity mask to pin the following code (calculations and thus
    // CPU load) to the desired CPU core.
    mask = (DWORD) SetThreadAffinityMask(GetCurrentThread(), affMask);

    ReadTSC(& lPerfCounterValueBeforeStart, & lStartPerfCounterValue,
      lTimeStampCounterBefore);

      static double secondsPassed;
      timerStepsPassed.QuadPart = lStartPerfCounterValue.QuadPart -
        lPerfCounterValueBeforeStart.QuadPart;
      secondsPassed = (double)(timerStepsPassed.QuadPart)
        // / (double)(lPerfCounterStepsPerSecond.QuadPart);
        * secondsPerTimerTick;
      //Get multiplier and voltage no matter if the reference clock will
      // be calculated. Else these values might _never_ be updated in GUI.
      multiplier = GetVoltageAndMultiplier(affMask, r_fVoltageInVolt);
      if( secondsPassed < MIN_TIME_SPAN_IN_S )
      {
  //		  volatile int i=0;
  //		  TickCount = GetTickCount();
        //orig value in CrystalCPUID: 100
  //      unsigned waitTimeInMs = 1;
        //apply load so the CPU does not enter sleep states where the
        //FSB could be clocked down.
        //while(GetTickCount() - TickCount < waitTimeInMs
      //    //i++
      //    ){
        //	i++;
        //	Sleep(0);
        //}
        double secondsBetweenTSCstartAndEnd;
#ifdef _DEBUG
        unsigned numLoopPasses = 0;
#endif
        do
        {
#ifdef SLEEP_ON_BUSY_WAITING
          //OperatingSystem::SleepMilliSeconds(0);
          PossiblyGiveTimeSliceToOtherProcesses();
#endif
          ReadTSC(& lPerfCounterValueBeforeEnd, & lEndPerfCounterValue,
            lTimeStampCounterAfter);

          secondsPassed = (double)(lEndPerfCounterValue.QuadPart -
            lPerfCounterValueBeforeEnd.QuadPart) /
            (double)(lPerfCounterStepsPerSecond.QuadPart);
          timerStepsPassed.QuadPart = lEndPerfCounterValue.QuadPart -
            lStartPerfCounterValue.QuadPart;
          secondsBetweenTSCstartAndEnd = (double)(timerStepsPassed.QuadPart) // /
            //(double)(lPerfCounterStepsPerSecond.QuadPart);
            * secondsPerTimerTick;
#ifdef _DEBUG
          ++ numLoopPasses;
#endif
        }while(
          //secondsBetweenTSCstartAndEnd
          //The longer the time span the more accurate when no CPU frequency changes.
          //"0.00005" (sec) had 1806 MHz instead of 1800 when no freq changes and accuracy when
            // ca. 40000 multiplier changes per second from min to max multiplier.
          //"0.00001" had 1830 Mhz
          //< 0.00001
          //0
          //when 50 timer steps at ca. 3.5 MHz Pentium M: 400 MHz instead of 600 MHz
          //timerStepsPassed.LowPart < numMinimumSteps

          secondsBetweenTSCstartAndEnd < waitTimeInSeconds
          && timerStepsPassed.QuadPart < numMinimumSteps
          );
#ifdef _DEBUG
        DEBUGN( "# loop passes: " << numLoopPasses);
#endif
//          secondsBetweenTSCstartAndEnd = (double)(timerStepsPassed.QuadPart) /
//            (double)(lPerfCounterStepsPerSecond.QuadPart);

        DEBUGN( "end TSC QPC: sec:" << secondsPassed
          << " TSC end - start: # QPC timerSteps:" << timerStepsPassed.QuadPart)
        //Ensure no other process etc. was executed between
        // "QueryPeformanceCounter" and "rdtsc".
        if( secondsPassed < MIN_TIME_SPAN_IN_S )
        {
          waitTimeInSeconds = (float) secondsBetweenTSCstartAndEnd;

//          error = 1.0f/(float)timerStepsPassed.QuadPart;
          numMinimumSteps = timerStepsPassed.LowPart;
  //        std::cout << " #timer steps:" << timerStepsPassed.QuadPart
  //          << " s waited:" << secondsBetweenTSCstartAndEnd
  //          //<< " timer steps/s:" << lPerfCounterStepsPerSecond.QuadPart
  //          << " error:" << error
  //          ;
          numTSCticksElapsed.QuadPart = lTimeStampCounterAfter.QuadPart -
            lTimeStampCounterBefore.QuadPart;
          clock = (double)(numTSCticksElapsed.QuadPart) / secondsBetweenTSCstartAndEnd /1000000.0;
          DEBUGN( "TSC diff:" << numTSCticksElapsed.QuadPart
            << " / \"seconds between TSC start and end\":" << secondsBetweenTSCstartAndEnd
            << " =" << (double) numTSCticksElapsed.QuadPart / secondsBetweenTSCstartAndEnd
            << " Hz")
        }
        else
        {
          DEBUGN( "time between 2 QueryPerformanceCounter calls sourrounding a"
            " 2nd or later rdtsc call is >= " << MIN_TIME_SPAN_IN_S)
          clock = - 2.0;
        }
      }
      else
      {
        DEBUGN( secondsPassed << ">=" << MIN_TIME_SPAN_IN_S
          << " -> no TSC diff"
          << " # timerStepsPassed:" << timerStepsPassed.QuadPart)
      }
    return clock;
  }

  void CalculateReferenceClockViaTSCdiff(
    float & r_fVoltageInVolt,
    float & r_fMultiplier,
    float & r_fReferenceClockInMHz
    )
  {
    static unsigned numTimerSteps;
    numTimerSteps = 100;
    static float waitTimeInSeconds = 0.00001;
    static double CPUclock;
    CPUclock = CPU::GetClockWithLoad(
      1 //<< wCoreID
      , r_fMultiplier //float & multiplier
      , numTimerSteps //unsigned & numMinimumSteps,
      , waitTimeInSeconds //float & waitTimeInSeconds,
      , r_fVoltageInVolt //float & r_fVoltageInVolt
      );
    r_fReferenceClockInMHz = CPUclock / r_fMultiplier;
  }

}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	double clock;
//  while( ! _kbhit() )
//  {
//    clock = GetClockWithLoad();
//      std::cout << "CPU freq:" << clock << "+-" << error*clock << "MHz" << std::endl;
//      Sleep(1000);
//  }
//  return 0;
//}

#endif //#ifndef GET_CPU_CLOCK_VIA_TSC_DIFF
