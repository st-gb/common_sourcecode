/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
/**Bln=Berlin:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_ID_prefix_h
   #define TU_Bln361095cmnSrc_ID_prefix_h

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
///Without "cmnSrc" (shorter) for convenience.
/**def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]nmSpcBgn" and "[...]nmSpcEnd" #define'd below.*/
  #define TU_Bln361095def(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]TU_Bln361095nmSpc" */
  #define TU_Bln361095nmSpc TU_Bln361095
  ///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095nmSpcBgn namespace TU_Bln361095{
  #define TU_Bln361095nmSpcEnd }
  #define TU_Bln361095use(suffix) TU_Bln361095nmSpc :: suffix

/**cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe(code):http://www.abbreviations.com/abbreviation/Source
 *   "common sourcecode" is the git repository these files are/should be in.
 * Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095cmnSrcNmSpc\
/** Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]cmnSrcNmSpc" */\
    TU_Bln361095 :: cmnSrc
  #if __cplusplus >= 201103 && defined  TU_Bln361095noCmnSrcScope
    namespace TU_Bln361095 = TU_Bln361095::cmnSrc;
  ///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
    #define TU_Bln361095cmnSrcNmSpcBgn namespace TU_Bln361095{
  #else
  ///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcNmSpcBgn namespace TU_Bln361095{namespace cmnSrc{
  #endif
  /**"}" times >>number of namespaces<<*/
  #define TU_Bln361095cmnSrcNmSpcEnd }}
  #define TU_Bln361095cmnSrcUse(suffix) TU_Bln361095cmnSrcNmSpc :: suffix
#else
///Without "cmnSrc" (shorter) for convenience.
  #define TU_Bln361095def(suffix) TU_Bln361095##suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095nmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095nmSpcBgn /** ->empty */
  #define TU_Bln361095nmSpcEnd /** ->empty */
  #define TU_Bln361095use(suffix) TU_Bln361095def(suffix)

///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcDef(suffix) TU_Bln361095cmnSrc ## suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095cmnSrcNmSpc /** ->empty */
  ///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcNmSpcBgn /** ->empty */
  #define TU_Bln361095cmnSrcNmSpcEnd /** ->empty */
  #define TU_Bln361095cmnSrcUse(suffix) TU_Bln361095cmnSrcDef(suffix)
#endif

#endif///Include guard