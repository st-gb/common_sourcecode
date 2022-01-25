#pragma once///Include guard

/**Adapted from
 * http://en.wikipedia.org/wiki/Inline_function#Nonstandard_extensions :*/
#ifdef _MSC_VER///MicroSoft C compiler present
  #define force_inline __forceinline
#elif defined(__GNUC__)///GNU C compiler present
  #define force_inline inline __attribute__((__always_inline__))
#elif defined(__CLANG__)///Clang C compiler present
  #if __has_attribute(__always_inline__)
    #define force_inline inline __attribute__((__always_inline__))
  #else
    #define force_inline inline
  #endif
#else
  #define force_inline inline
#endif
