///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
#ifdef TU_Bln361095usePrgmInclGrd
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
  /**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcCstdLibIDprefx_h
  #define TU_Bln361095cmnSrcCstdLibIDprefx_h

#ifdef __cplusplus
  #define TU_Bln361095CstdLibNmSpc CstdLib
  #define TU_Bln361095CstdLibNmSpcBgn namespace TU_Bln361095{\
    namespace TU_Bln361095CstdLibNmSpc{
  #define TU_Bln361095CstdLibNmSpcEnd }}
#else
  #define TU_Bln361095CstdLibNmSpc /**->empty*/
  #define TU_Bln361095CstdLibNmSpcBgn /**->empty*/
  #define TU_Bln361095CstdLibNmSpcEnd /**->empty*/
#endif

#endif///TU_Bln361095cmnSrcCstdLibIDprefx_h
