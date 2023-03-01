/**(c) Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif

/**Include guard supported by (nearly) all industry compilers:*/
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Bln=Berlin:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:http://www.abbreviations.com/OPSYS
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_Process_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_Process_ID_prefix_h

/**TU_Bln361095cmnSrcOpSysNmSpc,TU_Bln361095cmnSrcOpSysNmSpcBgn,
 * TU_BlncmnSrc361095OpSysNmSpcEnd */
#include "../ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcOpSysPrcssDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095cmnSrcOpSysPrcssNmSpc TU_Bln361095cmnSrcOpSysNmSpc ::\
    Process
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysPrcssNmSpcBgn TU_Bln361095cmnSrcOpSysNmSpcBgn\
    namespace Process{
  #define TU_Bln361095cmnSrcOpSysPrcssNmSpcEnd TU_Bln361095cmnSrcOpSysNmSpcEnd }
  #define TU_Bln361095cmnSrcOpSysPrcssUse(suffix)\
    TU_Bln361095cmnSrcOpSysPrcssNmSpc :: suffix
#else
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcOpSysPrcssDef(suffix)\
    TU_Bln361095cmnSrcOpSysDef(Prcss ## suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095cmnSrcOpSysPrcssNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysPrcssNmSpcBgn /** ->empty */
  #define TU_Bln361095cmnSrcOpSysPrcssNmSpcEnd /** ->empty */
  #define TU_Bln361095cmnSrcOpSysPrcssUse(suffix)\
    TU_Bln361095cmnSrcOpSysPrcssDef(suffix)
#endif

#endif///Include guard
