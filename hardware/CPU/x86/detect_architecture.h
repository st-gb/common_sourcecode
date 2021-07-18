///created: 2021 by Stefan Gebauer, M. Sc. Comp. Sc.

#pragma once///Include guard

///from https://sourceforge.net/p/predef/wiki/Architectures/

#ifdef __i386//defined by GNU C, Sun Studio, 
  #define Intel_x86
#endif

#ifdef _M_I86
  #define Intel_x86
#endif

#ifdef _M_IX86
  #define Intel_x86
#endif

#ifdef _X86_
  #define Intel_x86
#endif

