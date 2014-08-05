#pragma once

inline int AtomicFetchAndAdd(long * val, long add)
{
#ifdef _WIN32
  /** http://msdn.microsoft.com/de-de/library/windows/desktop/ms683614%28v=vs.85%29.aspx :
   * "This function generates a full memory barrier (or fence) to ensure that
   * memory operations are completed in order."
   */
  return InterlockedExchangeAdd(val, add);
#else
//  InterlockedIncrement
  /** https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html :
   *
   *  The definition given in the Intel documentation allows only for the use
   *  of the types int, long, long long as well as their unsigned counterparts.
   *  GCC will allow any integral scalar or pointer type that is 1, 2, 4 or 8 bytes in length.
   *
   *  Not all operations are supported by all target processors.
   *  If a particular operation cannot be implemented on the target processor,
   *  a warning will be generated and a call an external function will be generated.
   *  The external function will carry the same name as the builtin, with an
   *  additional suffix `_n' where n is the size of the data type.
   *
   *  "In most cases, these builtins are considered a full barrier.
   *  That is, no memory operand will be moved across the operation, either
   *  forward or backward. Further, instructions will be issued as necessary to
   *  prevent the processor from speculating loads across the operation and
   *  from queuing stores after the operation."
   */
  return __sync_add_and_fetch(val, add);
#endif
}
