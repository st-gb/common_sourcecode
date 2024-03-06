///(c)from 2022:Stefan Gebauer,Computer Science Master from TU Berlin
///@author Stefan Gebauer(TU Berlin matriculation number #361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard :

/**Define on compiler command line,for example for GCC:
 * (see http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :)
 * "gcc -D TU_Bln361095UsePrgmInclGuard"*/
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude: http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD: http://www.abbreviations.com/abbreviation/Guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers,
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**TU=Technical University
 * Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * Cmplr=CoMPiLeR
 * Frc=FoRCe: http://www.allacronyms.com/force/abbreviated
 * Inln=INLiNe: */\
 ! defined TU_Bln361095cmnSrc__Cmplr__FrcInln_h
   #define TU_Bln361095cmnSrc__Cmplr__FrcInln_h

///frc=force:http://www.allacronyms.com/force/abbreviated
/**Adapted from
 * http://en.wikipedia.org/wiki/Inline_function#Nonstandard_extensions :*/
#ifdef _MSC_VER///MicroSoft C compiler present
  #define TU_Bln361095frcInl __forceinline
#elif defined(__GNUC__)///GNU C compiler present
  #define TU_Bln361095frcInl inline __attribute__((__always_inline__))
/**by "static" avoid GCC warning "[...] is static but used in inline function
 * [...] which is not static" (used a static variable)
 * http://gcc.gnu.org/onlinedocs/gcc/Inline.html 
http://en.wikipedia.org/wiki/Inline_function#Storage_classes_of_inline_functions
 */
  #define TU_Bln361095frcSttcInln static TU_Bln361095frcInl
#elif defined(__CLANG__)///Clang C compiler present
  #if __has_attribute(__always_inline__)
    #define TU_Bln361095frcInl inline __attribute__((__always_inline__))
  #else
    #define TU_Bln361095frcInl inline
  #endif
#else
  #define TU_Bln361095frcInl inline
#endif

#define TU_Bln361095frcInln TU_Bln361095frcInl
#ifndef TU_Bln361095frcSttcInln
/**Useful when using a static variable in an inline function to avoid compiler
 * warning(s).*/
  #define TU_Bln361095frcSttcInln static TU_Bln361095frcInl
#endif

#endif///include guard
