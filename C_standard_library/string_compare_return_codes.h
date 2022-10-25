///(c)from 2015:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.15Feb2015 by Stefan Gebauer(TU Berlin,matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
  /**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcCstdLib_strcmp_h
  #define TU_Bln361095cmnSrcCstdLib_strcmp_h

#include "ID_prefix.h"///TU_Bln361095CstdLibNmSpcBgn,TU_Bln361095CstdLibNmSpcEnd

#ifdef __cplusplus
  #define TU_Bln361095StrcmpNmSpc strcmp
  #define TU_Bln361095CstdLibStrcmpDef(suffix) suffix
  #define TU_Bln361095CstdLibStrcmpUse(suffix) TU_Bln361095CstdLibNmSpc\
    TU_Bln361095StrcmpNmSpc :: suffix
#else
  #define TU_Bln361095StrcmpNmSpc /**->empty*/
  #define TU_Bln361095CstdLibStrcmpDef(suffix)\
   TU_Bln361095CstdLibDef(Strcmp ## suffix)
  #define TU_Bln361095CstdLibStrcmpUse(suffix)\
    TU_Bln361095CstdLibStrcmpDef(suffix)
#endif

TU_Bln361095CstdLibNmSpcBgn

#ifdef __cplusplus
namespace TU_Bln361095StrcmpNmSpc
{
#endif
/** http://pubs.opengroup.org/onlinepubs/009695399/functions/strcmp.html :
 * "int strcmp(const char *s1, const char *s2);"
 * "Upon completion, strcmp() shall return an integer greater than, equal to,
 * or less than 0, if the string pointed to by s1 is greater than, equal to,
 * or less than the string pointed to by s2, respectively."*/
enum TU_Bln361095CstdLibStrcmpDef(RtrnCodes){
  /**Lft=LeFT:http://www.allacronyms.com/left/abbreviated*/
  TU_Bln361095CstdLibStrcmpDef(LftStrLss) = -1,
  /**Eql=EQuaL:http://www.abbreviations.com/abbreviation/Equal*/
  TU_Bln361095CstdLibStrcmpDef(EqlStrs) = 0,
  /*RghtStrLss*//**Gtr=GreaTR:http://www.allacronyms.com/greater/abbreviated*/
  TU_Bln361095CstdLibStrcmpDef(LftStrGtr)};
#ifdef __cplusplus
}
#endif

TU_Bln361095CstdLibNmSpcEnd

#endif///! defined TU_Bln361095cmnSrcCstdLib_strcmp_h
