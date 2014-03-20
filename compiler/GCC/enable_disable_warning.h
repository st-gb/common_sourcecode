/*
 * enable_disable_write_strings_warning.h
 *
 *  Created on: 20.06.2013
 *      Author: Stefan
 */

#ifndef ENABLE_DISABLE_WARNING_H_
#define ENABLE_DISABLE_WARNING_H_

  /** from http://dbp-consulting.com/tutorials/SuppressingGCCWarnings.html */
  #if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
    #define GCC_DIAG_STR(s) #s
    #define GCC_DIAG_JOINSTR(x,y) GCC_DIAG_STR(x ## y)
  # define GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
  # define GCC_DIAG_PRAGMA(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
  # if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406 //GNUC > 4.06
  #  define GCC_DIAG_OFF(x) \
       GCC_DIAG_PRAGMA(push) \
       GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
  #  define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(pop)
  # else
  #  define GCC_DIAG_OFF(x) GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
  #  define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(warning GCC_DIAG_JOINSTR(-W,x))
  # endif
  #else
  # define GCC_DIAG_OFF(x)
  # define GCC_DIAG_ON(x)
  #endif

#endif //#ifndef ENABLE_DISABLE_WARNING_H_
