/**(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

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
/**Bln=Berlin: http://www.acronymfinder.com/Berlin-(Bln).html 
 * Typ=TYPe:
 * Uint=Unsigned INTeger */\
 !defined TU_Bln361095cmnSrc__dataType__bigUnit__bigUint_ID_prefix_h
  #define TU_Bln361095cmnSrc__dataType__bigUnit__bigUint_ID_prefix_h

#ifdef __cplusplus
  #define TU_Bln361095dataTypeBigUintDef(suffix)\
    TU_Bln361095dataTypeBigNum##suffix
  #define TU_Bln361095dataTypeBigUintUse(suffix)\
    TU_Bln361095dataTypeBigNumDef(suffix)
#else
  #define TU_Bln361095dataTypeBigUintDef(suffix)\
    TU_Bln361095dataTypeBigUint##suffix
  #define TU_Bln361095dataTypeBigUintUse(suffix)\
    TU_Bln361095dataTypeBigUintDef(suffix)  
#endif

#include <ID_prefix.h>///TU_Bln361095NmSpc

#ifdef __cplusplus
  #define TU_Bln361095_16B_uIntDef(identifier)\
    /**Definitions are inside \@see TU_Bln361095_16B_uIntNmSpc, so only use
     * identifier*/\
      identifier
  #define TU_Bln361095_16B_uIntNmSpc TU_Bln361095nmSpc :: _16B_uInt
  #define TU_Bln361095_16B_uIntNmSpcBgn\
    TU_Bln361095nmSpcBgn namespace _16B_uInt{
  #define TU_Bln361095_16B_uIntNmSpcEnd TU_Bln361095nmSpcEnd }
  #define TU_Bln361095_16B_uIntUse(identifier)\
    TU_Bln361095_16B_uIntNmSpc :: identifier
#else///"C" programming language
  #define TU_Bln361095_16B_uIntNmSpc
  #define TU_Bln361095_16B_uIntNmSpcBgn
  #define TU_Bln361095_16B_uIntNmSpcEnd
  #define TU_Bln361095_16B_uIntDef(identifier)\
    TU_Bln361095def(_16B_uInt##identifier)
  /**In the "C" language calling and deckaration the same prefix character
   * string is used.*/
  #define TU_Bln361095_16B_uIntUse(identifier)\
    TU_Bln361095_16B_uIntDef(identifier)
#endif

#endif///Include guard