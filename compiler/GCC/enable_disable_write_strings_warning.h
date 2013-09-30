/*
 * enable_disable_write_strings_warning.h
 *
 *  Created on: 20.06.2013
 *      Author: Stefan
 */

#ifndef ENABLE_DISABLE_WRITE_STRINGS_WARNING_H_
#define ENABLE_DISABLE_WRITE_STRINGS_WARNING_H_

  //from http://dbp-consulting.com/tutorials/SuppressingGCCWarnings.html
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

#if(__GNUC__ > 3) //&& defined(__MINGW32__) /* pragma only for GNUC >= version 4 */
    /*DISable warning, from */
    /*http://stackoverflow.com/questions/59670/how-to-get-rid-of-deprecated-conversion-from-string-constant-to-char-warning*/
    /*: "I believe passing -Wno-write-strings to gcc will suppress this warning."*/
  #define IGNORE_WRITE_STRINGS_WARNING _Pragma("GCC diagnostic ignored \"-Wwrite-strings\"")

#else
  #define IGNORE_WRITE_STRINGS_WARNING /* empty */
#endif
#if(__GNUC__ > 3) /* pragma for GNUC >=4 */
  #define ENABLE_WRITE_STRINGS_WARNING \
    /*http://stackoverflow.com/questions/59670/how-to-get-rid-of-deprecated-conversion-from-string-constant-to-char-warning*/ \
    /* : "I believe passing -Wno-write-strings to gcc will suppress this warning."*/ \
    /*ENable g++ "deprecated conversion from string constant to 'char*'" warning*/ \
    /* #pragma GCC diagnostic warning "-Wwrite-strings"*/ \
    _Pragma("GCC diagnostic warning \"-Wwrite-strings\"")
#else
  #define ENABLE_WRITE_STRINGS_WARNING /* empty */
#endif

#endif /* ENABLE_DISABLE_WRITE_STRINGS_WARNING_H_ */
