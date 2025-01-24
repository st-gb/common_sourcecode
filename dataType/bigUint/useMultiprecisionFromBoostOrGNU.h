/**(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
  /**Non-standard include guard:supported by many, but not all industry compilers:
   * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Typ=TYPe: 
 * Uint=Unsigned INTeger */\
 !defined TU_Bln361095dataTyp__bigUint__useMultiprecisionFromBoostOrGNU_h
  #define TU_Bln361095dataTyp__bigUint__useMultiprecisionFromBoostOrGNU_h

///Stefan Gebauer's(TU Berlin matricul. num. 361095) ~"cmnSrc" repository files:
 #include <ID_prefix.h>///TU_Bln361095Def(...)
 #include <compiler/force_inline.h>///TU_Bln361095frcInln

/**2^64-1= 18.446.744.073.709.551.615=20 digits * 2 + "*(2^64)+" + character
 * string terminating \0 character
 * = 16 hexadecimal digits
 * max dec num = 3,4028236692093846346337460743177e+38 */
#define TU_Bln361095_16B_UintMaxNumCharsForDecNum 50

//#ifdef __cplusplus///C++-specific stuff
//#ifdef TU_Bln361095boostRootDir
#ifdef useBoostMultiPrecisionArithmLib
  #include "bigUintBoostMultiPrecisionArithmLib.h"
#else///no C++ =>compiled by C compiler
  #ifdef useGNUmultiPrecisionArithmLib
  #pragma message "useGNUmultiPrecisionArithmLib defined"
    #include "bigUintGNUmultiPrecisionArithmLib.h"
  #else
  //  #pragma message "useGNUmultiPrecisionArithmLib NOT defined"
  #endif
  #define UintB16TypRef(identifier) (& identifier)
#endif///This file is compiled with a C compiler.

#endif///Include guard