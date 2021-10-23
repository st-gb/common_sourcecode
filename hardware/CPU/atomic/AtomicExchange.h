#pragma once

#ifdef _WIN32
  #include <windows.h> //InterlockedExchange
#endif

/** Compare-And-Swap operations have max. pointer size (aligned at multiple of
 * this size?).
 * https://en.wikipedia.org/wiki/C_data_types :
 * int has at least 2 or 4 byte, long
 * "The type int should be the integer type that the target processor is most
 *  efficiently working with." */
typedef long AtomicExchType;

/** Writes value @param val into address of @param Target as 1 atomic operation. 
    -> thread-safe */
inline long AtomicExchange(
  /** https://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/Atomic-Builtins.html :
   * "The definition given in the Intel documentation allows only for the use of
   * the types int, long, long long as well as their unsigned counterparts. GCC
   * will allow any integral scalar or pointer type that is 1, 2, 4 or 8 bytes
   * in length." */
  long * Target, long val)
{
#ifdef _WIN32
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
