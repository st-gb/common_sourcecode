/**(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:http://www.abbreviations.com/OPSYS
 * ID=identifier:http://www.abbreviations.com/abbreviation/identifier */\
 ! defined TU_Bln361095cmnSrc_OpSys_Unix_CPUFreq_ID_prefix_h
   #define TU_Bln361095cmnSrc_OpSys_Unix_CPUFreq_ID_prefix_h

/**TU_Bln361095cmnSrcOpSysUnixNmSpc,TU_Bln361095cmnSrcOpSysUnixNmSpcBgn,
 * TU_Bln361095cmnSrcOpSysUnixDef(...) */
#include "../ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put Definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpc\
    TU_Bln361095cmnSrcOpSysUnixNmSpc :: CPUFreq
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
#define TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcBgn TU_Bln361095OpSysUnixNmSpcBgn\
    namespace CPUFreq{
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcEnd\
    TU_Bln361095cmnSrcOpSysUnixNmSpcEnd }
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(suffix)\
    TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(suffix)\
    TU_Bln361095cmnSrcOpSysUnixDef(CPUFreq##suffix)
//    TU_Bln361095cmnSrcOpSysUnixCPUFreq ## suffix
///"C" language has no namespaces->Replace with empty character string.
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpc
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcBgn
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcEnd
  #define TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(suffix)\
    TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(suffix)
#endif

TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcBgn

extern /*static*/ const char TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(
///fmt=format str=string
  availGvrnrsAbsFilePathFmtStr[]);

TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcEnd

#endif///Include guard