///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers,
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all compilers:
#ifndef TU_Bln361095cmnSrcCmplrFrcInln_h
#define TU_Bln361095cmnSrcCmplrFrcInln_h

///frc=force:http://www.allacronyms.com/force/abbreviated
/**Adapted from
 * http://en.wikipedia.org/wiki/Inline_function#Nonstandard_extensions :*/
#ifdef _MSC_VER///MicroSoft C compiler present
  #define TU_Bln361095frcInl __forceinline
#elif defined(__GNUC__)///GNU C compiler present
  #define TU_Bln361095frcInl inline __attribute__((__always_inline__))
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

#endif///#ifndef TU_Bln361095cmnSrcCmplrFrcInln_h
