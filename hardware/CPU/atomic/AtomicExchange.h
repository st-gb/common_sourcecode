#pragma once

#ifdef _WIN32
  #include <windows.h> //InterlockedExchange
#endif

/** Writes value @param val into address of @param Target as 1 atomic operation. 
    -> thread-safe */
inline long AtomicExchange(long * Target, long val)
{
#ifdef _WIN32
  /** http://msdn.microsoft.com/en-us/library/windows/desktop/ms683590%28v=vs.85%29.aspx
   * "The function returns the initial value of the Target parameter." */
  return InterlockedExchange(Target, val);
#else
#ifdef __GNUC__
  /** https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html :
   *
   * "That is, if the current value of *ptr is oldval, then write newval into *ptr. "
   * " The “val” version returns the contents of *ptr before the operation." */
  return __sync_val_compare_and_swap(
    Target /** type *ptr */
    , * Target //type oldval
    , val /** type newval */
    );
#endif
#endif
}
