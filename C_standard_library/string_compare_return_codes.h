///(c)from 2015:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.15Feb2015 by Stefan Gebauer(TU Berlin,matriculation number 361095)

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
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc_CstdLib_strcmp_h
   #define TU_Bln361095cmnSrc_CstdLib_strcmp_h

/**TU_Bln361095CstdLibNmSpc, TU_Bln361095CstdLibNmSpcBgn,
 * TU_Bln361095CstdLibNmSpcEnd */
#include "CstdLib_ID_prefix.h"

/**Use the following preprocessor macros in source code for example to enable
 * both C and C++.*/
#ifdef __cplusplus
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095CstdLibStrcmpDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]StrcmpNmSpc".*/
  #define TU_Bln361095CstdLibStrcmpNmSpc TU_Bln361095CstdLibNmSpc :: strcmp
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CstdLibStrcmpNmSpcBgn\
    TU_Bln361095CstdLibNmSpcBgn namespace strcmp{
  #define TU_Bln361095CstdLibStrcmpNmSpcEnd TU_Bln361095CstdLibNmSpcEnd }
  #define TU_Bln361095CstdLibStrcmpUse(suffix)\
    TU_Bln361095CstdLibStrcmpNmSpc :: suffix
#else
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095CstdLibStrcmpDef(suffix)\
   TU_Bln361095CstdLibDef(Strcmp ## suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
/**"C" language has no namespaces->Replace with empty character string.*/
  #define TU_Bln361095CstdLibStrcmpNmSpc /**->empty*/
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CstdLibStrcmpNmSpcBgn /**->empty*/
  #define TU_Bln361095CstdLibStrcmpNmSpcEnd /**->empty*/
  #define TU_Bln361095CstdLibStrcmpUse(suffix)\
    TU_Bln361095CstdLibStrcmpDef(suffix)
#endif

TU_Bln361095CstdLibStrcmpNmSpcBgn

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
  TU_Bln361095CstdLibStrcmpDef(LftStrGtr)
  };

TU_Bln361095CstdLibStrcmpNmSpcEnd

#endif///include guard
