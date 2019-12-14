/*
 * ReadTimeStampCounter.h
 *
 *  Created on: Jun 13, 2010
 *      Author: Stefan
 */

#ifndef READTIMESTAMPCOUNTER_H_
#define READTIMESTAMPCOUNTER_H_

#include <Controller/SetThreadAffinityMask.h> //SetThreadAffinityMask(...)
#include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUGN(...)
#include <winnt.h> //for ULONGLONG
#include <windef.h> //for DWORD
#include <stdint.h>///uint32_t
#include <inttypes.h> //uint64_t under Linux

//From CrystalCPUID:
//static void rdtsc(DWORD *EAX, DWORD *EDX)
//{
//  _asm { cpuid }
//#ifndef _X86_64
//	DWORD A, D;
//	_asm {
//		rdtsc
//		mov A, eax
//		mov D, edx
//	}
//	*EAX = A;
//	*EDX = D;
//#else
//	ULONG64 ul64;
//	ul64 = __rdtsc();
//	*EDX = (DWORD)(ul64 >> 32);
//	*EAX = (DWORD)ul64;
//#endif
//}

//TODO use affinity mask for reading the TSC
/** http://en.wikipedia.org/wiki/Time_Stamp_Counter:
* "[...]whether all cores (processors) have identical values in their
* time-keeping registers. There is no promise that the timestamp counters of
* multiple CPUs on a single motherboard will be synchronized.
* In such cases, programmers can
* only get reliable results by locking their code to a single CPU."
* ->on a motherboard CPU/ CPU core 0 may have TSC freq of 1000 MHz,
* CPU/ CPU core 1 may have TSC freq of 1200 MHz.
* If not using affinity mask TSC may be read on CPU0 and afterwards on CPU1.*/

//#ifdef _MSC_VER /** MicroSoft Compiler */
#ifdef _WIN32 /** Microsoft WINdows (also 64 bit) */
/** For MicroSoft Visual C++ /MinGW: ReadTimeStampCounter() already defined in 
 * <winnt.h> */
  #undef ReadTimeStampCounter
#endif
  /** @param lowmostBits : "uint32_t" because this matches the size of the EAX 
   *   CPU register */
  inline //ULONGLONG
    void ReadTimeStampCounter(
      uint32_t & lowmostBits
      , uint32_t & highmostBits
      )
  {
//    unsigned a, d;
   // //Adapted from http://www.fftw.org/cycle.h:
   // ULONGLONG ull ;
   // __asm {
    //RDTSC
   // ret
    //mov ull, edx
    //mov ull, eax
   // }
   // return ull ;
//    return __rdtsc() ;
//#else //__MINGW__ etc.
    //from http://www.cs.wm.edu/~kearns/001lab.d/rdtsc.html:
    __asm__ volatile("rdtsc" : "=a" (lowmostBits), "=d" (highmostBits));
    //return ((unsigned long long)a) | (((unsigned long long)d) << 32) ;
  }
  inline ULONGLONG ReadTimeStampCounter()
  {
    unsigned a, d;
   // //Adapted from http://www.fftw.org/cycle.h:
   // ULONGLONG ull ;
   // __asm {
    //RDTSC
   // ret
    //mov ull, edx
    //mov ull, eax
   // }
   // return ull ;
//    return __rdtsc() ;
//#else //__MINGW__ etc.
    //from http://www.cs.wm.edu/~kearns/001lab.d/rdtsc.html:
    __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
    return ((unsigned long long)a) | (((unsigned long long)d) << 32) ;
  }
//#endif

/** @param lowmostBits : "uint32_t" because this matches the size of the EAX 
   *   CPU register */
inline void ReadTSCinOrder(
  uint32_t & lowmostBits ,
  uint32_t & highmostBits ,
  DWORD dwThreadAffinityMask
  )
{
//  if( ::SetThreadAffinityMask(::GetCurrentThread() , dwThreadAffinityMask) )
  {
    /** see http://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf page 3/12 : 
     * cpuid _before_ rdtsc :
      "cpuid ; force all previous instructions to complete
       rdtsc ; read time stamp counter"  */
    //from http://en.wikipedia.org/wiki/CPUID
    // #Accessing_the_id_from_other_languages:
    asm ( "mov 1, %%eax; " // a into eax
           "cpuid" ) ;
    ReadTimeStampCounter(lowmostBits, highmostBits ) ;
//    return TRUE ;
  }
}

/** From http://en.wikipedia.org/wiki/Time_Stamp_Counter#C.2B.2B
 *   possibly set the thread affinity mask before because the TSC may differ
 *   between different CPU cores */
__inline__ uint64_t ReadTSCinOrderFromEnglishWikipedia(void)
{
    /** According to https://en.wikipedia.org/wiki/Time_Stamp_Counter#C.2B.2B :
      *  " force every preceding instruction to complete before before allowing 
      *  the program to continue" */
    /** see https://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf page 3/12 :
     *  cpuid is placed _before_ rdtsc */
    __asm__ __volatile__ (
      "        xorl %%eax,%%eax \n"
      "        cpuid"      // serialize
      //TODO g++ 4.x complains if using x86 CPU register "rbx"
      //  it uses it for Position-Independent Code (PIC) for dynamic libraries?
      ::: "%rax", "%rbx", "%rcx", "%rdx");
    /** The following doesn't seem to function. */
//    asm ( "mov 1, %eax; " // a into eax
//       "cpuid" ) ;    
    uint32_t lo, hi;
    /* We cannot use "=A", since this would use %rax on x86_64 and return only 
     * the lower 32bits of the TSC */
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));    
    return (uint64_t)hi << 32 | lo;
}

namespace NS_SetThreadAffinityMask
{
  inline unsigned ReadTimeStampCounter(
    DWORD dwThreadAffinityMask,
    uint64_t & rdtscValue)
  {
    DWORD dwPreviousAffMask = OperatingSystem::SetThreadAffinityMask( //::GetCurrentThread() ,
        dwThreadAffinityMask) ;
    if( dwPreviousAffMask )
    {
      rdtscValue = ::ReadTimeStampCounter();
      return 0;
    }
    return 1;
  }

  inline ULONGLONG ReadTSCinOrder( DWORD dwThreadAffinityMask )
  {
    ULONGLONG ull = 0 ;
    DEBUGN(/*"inline ULONGLONG ReadTSCinOrder( DWORD dwThreadAffinityMask ) "*/"begin")
    /** http://en.wikipedia.org/wiki/Rdtsc:
    * "There is no promise that the timestamp counters of multiple CPUs on a
    * single motherboard will be synchronized. In such cases, programmers can
    * only get reliable results by locking their code to a single CPU." */
    DWORD dwPreviousAffMask = OperatingSystem::SetThreadAffinityMask( //::GetCurrentThread() ,
        dwThreadAffinityMask) ;
    if( dwPreviousAffMask )
    {
      //http://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf:
  //    CPUID(); //"force all previous instructions to complete"
      //from http://en.wikipedia.org/wiki/CPUID
      // #Accessing_the_id_from_other_languages:
  //    asm ( "mov 1, %%eax; " // a into eax
  //           "cpuid" ) ;

      //from http://ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#s3
      //  see table "Intel Code             |      AT&T Code"

  ////    //call CPUID function 1:
  //    asm ( "mov $1, %eax") ; //write "1" into register "eax" for "CPUID fct. "1"
  ////    //http://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf,
  ////    //  chapter 3.1. Out-of-Order-Execution
  //    asm ( "cpuid" ) ; //this forces all previous operations to complete.
  //    ull = ReadTimeStampCounter() ;

      ull = ReadTSCinOrderFromEnglishWikipedia();

      /** Restore the previous thread affinity mask.*/
      //TODO program crashed (SIGSEGV)  when this line is uncommented
//      OperatingSystem::SetThreadAffinityMask( dwPreviousAffMask ) ;
    }
    DEBUGN(/*"inline ULONGLONG ReadTSCinOrder( DWORD dwThreadAffinityMask ) "*/"end")
    return ull ;
  }
}

#endif /* READTIMESTAMPCOUNTER_H_ */
