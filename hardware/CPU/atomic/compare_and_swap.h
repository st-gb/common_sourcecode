#pragma once //

/** @return true if exchanged */
inline int boolCompareAndSwap(long int * Destination, int oldval, int newval)
{
//#ifdef __GCC__
  //https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html
  //return __sync_val_compare_and_swap();
  //The “bool” version returns true if the comparison is successful and newval was written.
//  return __sync_bool_compare_and_swap(p, oldval, newval);
//#endif
  return
    /** http://msdn.microsoft.com/de-de/library/windows/desktop/ms683560%28v=vs.85%29.aspx :
     * "The function returns the initial value of the Destination parameter."
     *
     * The function compares the Destination value with the Comparand value.
     * If the Destination value is equal to the Comparand value, the Exchange
     * value is stored in the address specified by Destination.
     * Otherwise, no operation is performed. */
    InterlockedCompareExchange(
      Destination, //A pointer to the destination value.
      newval, //The exchange value.
      oldval //The value to compare to Destination.
      ) //!= newval;
    == oldval;
}

