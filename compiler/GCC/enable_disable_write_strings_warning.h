/*
 * enable_disable_write_strings_warning.h
 *
 *  Created on: 20.06.2013
 *      Author: Stefan
 */

#ifndef ENABLE_DISABLE_WRITE_STRINGS_WARNING_H_
#define ENABLE_DISABLE_WRITE_STRINGS_WARNING_H_

#if __GNUC__ > 3 /* pragma only for GNUC >= version 4 */
  #define IGNORE_WRITE_STRINGS_WARNING \
    /*DISable warning, from
    http://stackoverflow.com/questions/59670/how-to-get-rid-of-deprecated-conversion-from-string-constant-to-char-warning
    : "I believe passing -Wno-write-strings to gcc will suppress this warning."*/ \
    #pragma GCC diagnostic ignored "-Wwrite-strings"
#else
  #define IGNORE_WRITE_STRINGS_WARNING /* empty */
#endif
#if __GNUC__ > 3 /* pragma for GNUC >=4 */
  #define ENABLE_WRITE_STRINGS_WARNING \
    /*http://stackoverflow.com/questions/59670/how-to-get-rid-of-deprecated-conversion-from-string-constant-to-char-warning*/ \
    /* : "I believe passing -Wno-write-strings to gcc will suppress this warning."*/ \
    /*ENable g++ "deprecated conversion from string constant to 'char*'" warning*/ \
    #pragma GCC diagnostic warning "-Wwrite-strings"
#else
  #define ENABLE_WRITE_STRINGS_WARNING /* empty */
#endif

#endif /* ENABLE_DISABLE_WRITE_STRINGS_WARNING_H_ */
