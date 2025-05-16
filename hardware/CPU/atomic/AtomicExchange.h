///(c)from 2014 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
///Created ca.05Aug2014 by Stefan Gebauer(TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * Exchng=EXCHaNGe */\
 ! defined TU_Bln361095cmnSrc__CPU__atomicExchg_h
   #define TU_Bln361095cmnSrc__CPU__atomicExchg_h

///Stefan Gebauer's(TU Berlin matricul. num. 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095MicroSoftWindows
 #include <OperatingSystem/Windows/MicrosoftWindows.h>
 ///TU_Bln361095hardwareCPUdef(...)
 #include <hardware/CPU/hardwareCPU_ID_prefix.h>

#ifdef TU_Bln361095MicroSoftWindows
/**http://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockedexchange
 * :"Header winnt.h (include Windows.h)"*/
  #include <windows.h>///InterlockedExchange(...)
#endif

TU_Bln361095CPUnmSpcBgn
 
/** Compare-And-Swap operations have max. pointer size (aligned at multiple of
 * this size?).
 * https://en.wikipedia.org/wiki/C_data_types :
 * int has at least 2 or 4 byte, long
 * "The type int should be the integer type that the target processor is most
 *  efficiently working with." */
///Exch=EXCHange:http://www.allacronyms.com/exchange/abbreviated
typedef long AtomicExchType;

///Xchg=eXCHanGe:http://www.allacronyms.com/exchange/abbreviated
///Typ=TYPe:http://www.abbreviations.com/abbreviation/Type
///Use precise type name because this (only) applies to CPU.
typedef long TU_Bln361095hardwareCPUdef(atomicXchgTyp);

/**@brief Writes value @param val into address of @see Target as 1 atomic
 *  operation->thread-safe
 * @param Target may be 32 bit on MSVC Windows: */
inline long TU_Bln361095hardwareCPUdef(atomicXchg)(
  /** https://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/Atomic-Builtins.html :
   * "The definition given in the Intel documentation allows only for the use of
   * the types int, long, long long as well as their unsigned counterparts. GCC
   * will allow any integral scalar or pointer type that is 1, 2, 4 or 8 bytes
   * in length." */
  long * Target, long val)
{
#ifdef TU_Bln361095MicroSoftWindows
  /** http://msdn.microsoft.com/en-us/library/windows/desktop/ms683590%28v=vs.85%29.aspx
   * "The function returns the initial value of the Target parameter." 
   * "This function generates a full memory barrier (or fence) to ensure that 
   *  memory operations are completed in order." 
   *  https://docs.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-interlockedexchange
   *  : "LONG" data type */
  return InterlockedExchange(Target, val);
#else
#ifdef __GNUC__
  /** https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html :
   *
   * "That is, if the current value of *ptr is oldval, then write newval into *ptr. "
   * " The �val� version returns the contents of *ptr before the operation." */
//  return __sync_val_compare_and_swap(
//    Target /** type *ptr */
//    , * Target //type oldval
//    , val /** type newval */
//    );
   /** https://gcc.gnu.org/onlinedocs/gcc-4.4.5/gcc/Atomic-Builtins.html:
   *  "[...] rather an atomic exchange operation. It writes value into *ptr,
   *   and returns the previous contents of *ptr." */
  return __sync_lock_test_and_set(Target, val);
#endif
#endif
}

TU_Bln361095CPUnmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcCPUatomicExchg_h