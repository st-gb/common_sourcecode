///(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
///@author Stefan Gebauer(TU Berlin matriculation number 361095)

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
 * std=STandarD:http://www.abbreviations.com/abbreviation/standard
 * Lib=LIBrary http://www.abbreviations.com/abbreviation/Library */\
 ! defined TU_Bln361095cmnSrc_CstdLib_fseek_h
   #define TU_Bln361095cmnSrc_CstdLib_fseek_h

///Bln361095cmnSrcCstdLibNmSpcBgn,Bln361095cmnSrcCstdLibNmSpcEnd
#include "ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put Definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095CstdLib_fseekDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095CstdLib_fseekNmSpc TU_Bln361095cmnSrcCstdLibNmSpc ::fseek
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CstdLib_fseekNmSpcBgn TU_Bln361095cmnSrcCstdLibNmSpcBgn\
    namespace fseek{
  #define TU_Bln361095CstdLib_fseekNmSpcEnd TU_Bln361095cmnSrcCstdLibNmSpcEnd }
  #define TU_Bln361095CstdLib_fseekRtrnCodeDef(suffix) suffix
  #define TU_Bln361095CstdLib_fseekRtrnCodeNmSpc TU_Bln361095CstdLib_fseekNmSpc\
    :: rtrnCode
  #define TU_Bln361095CstdLib_fseekRtrnCodeNmSpcBgn \
    TU_Bln361095CstdLib_fseekNmSpcBgn namespace rtrnCode{
  #define TU_Bln361095CstdLib_fseekRtrnCodeNmSpcEnd \
    TU_Bln361095CstdLib_fseekNmSpcEnd }
  #define TU_Bln361095CstdLib_fseekRtrnCodeUse(suffix)\
    TU_Bln361095CstdLib_fseekRtrnCodeNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095CstdLib_fseekDef(suffix)\
    TU_Bln361095cmnSrcCstdLibDef(fseek##suffix)
///"C" language has no namespaces->Replace with empty character string.
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095CstdLib_fseekNmSpc /** ->empty */
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095CstdLib_fseekNmSpcBgn /** ->empty */
  #define TU_Bln361095CstdLib_fseekNmSpcEnd /** ->empty */
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095CstdLib_fseekRtrnCodeDef(suffix)\
    TU_Bln361095CstdLib_fseekDef(RtrnCode ## suffix)
  #define TU_Bln361095CstdLib_fseekRtrnCodeNmSpc
  #define TU_Bln361095CstdLib_fseekRtrnCodeNmSpcBgn
  #define TU_Bln361095CstdLib_fseekRtrnCodeNmSpcEnd
  #define TU_Bln361095CstdLib_fseekRtrnCodeUse(suffix)\
   TU_Bln361095CstdLib_fseekRtrnCodeDef(suffix)
#endif

TU_Bln361095CstdLib_fseekRtrnCodeNmSpcBgn

enum TU_Bln361095CstdLib_fseekDef(RtrnCds){
/** http://pubs.opengroup.org/onlinepubs/007904975/functions/fseek.html :
 * "Otherwise, they shall return -1 and set errno to indicate the error." */
  TU_Bln361095CstdLib_fseekRtrnCodeDef(Error) = -1,
/** http://pubs.opengroup.org/onlinepubs/007904975/functions/fseek.html :
 * "The fseek() [...] functions shall return 0 if they succeed."*/
/*const unsigned*/TU_Bln361095CstdLib_fseekRtrnCodeDef(Success) = 0
};

TU_Bln361095CstdLib_fseekRtrnCodeNmSpcEnd

#endif///Include guard