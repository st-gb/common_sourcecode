/**(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number:361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Bln=Berlin:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * Fl=FiLe
 * Sys=SYStem:http://www.abbreviations.com/abbreviation/system
 * Sz=SiZe:http://www.abbreviations.com/abbreviation/size */\
 ! defined TU_Bln361095cmnSrc_FlSys_Fl_getFlSz_h
   #define TU_Bln361095cmnSrc_FlSys_Fl_getFlSz_h

///C standard library header files:
#include <stdio.h>///struct FILE

/**TU_Bln361095cmnSrcFlSysNmSpc,TU_Bln361095cmnSrcFlSysNmSpcBgn,
 * TU_Bln361095cmnSrcFlSysDef */
#include "../ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cpluplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095cmnSrcFlSysGetFlSzDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095cmnSrcFlSysGetFlSzNmSpc TU_Bln361095cmnSrcFlSysNmSpc ::\
    GetFlSz
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcFlSysGetFlSzNmSpcBgn \
    TU_Bln361095cmnSrcFlSysNmSpcBgn namespace GetFlSz{
  #define TU_Bln361095cmnSrcFlSysGetFlSzNmSpcEnd \
    TU_Bln361095cmnSrcFlSysNmSpcEnd }
  #define TU_Bln361095cmnSrcFlSysGetFlSzUse(suffix)\
    TU_Bln361095cmnSrcFlSysGetFlSzNmSpc :: suffix
#else
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095cmnSrcFlSysGetFlSzDef(suffix) TU_Bln361095cmnSrcFlSysDef(\
    GetFlSz ## suffix)
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095cmnSrcFlSysGetFlSzNmSpc /** ->empty */
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095cmnSrcFlSysGetFlSzNmSpcBgn /** ->empty */
  #define TU_Bln361095cmnSrcFlSysGetFlSzNmSpcEnd /** ->empty */
  #define TU_Bln361095cmnSrcFlSysGetFlSzUse(suffix)\
    TU_Bln361095cmnSrcFlSysGetFlSzDef(suffix)
#endif

TU_Bln361095cmnSrcFlSysGetFlSzNmSpcBgn

enum TU_Bln361095cmnSrcFlSysGetFlSzDef(Rslt){
  TU_Bln361095cmnSrcFlSysGetFlSzDef(Success) = 0,
  TU_Bln361095cmnSrcFlSysGetFlSzDef(SeekToBgnPosError),
  TU_Bln361095cmnSrcFlSysGetFlSzDef(SeekToEndError)
  };

/**Make inline to avoid multiple definitions if _this_ file is included from
 * more than 1 C(++) source file.
 * Must be declared (when [indirectly] included from a "C" source file) "static
 * inline" to avoid:
 * -multiple definitions of this fuction
 * -"undefined reference" to this fuction */
static inline int TU_Bln361095cmnSrcFlSysDef(GetFileSizeInB)(FILE * p_File,
  long * p_fileSizeInB)
{
  const long currFilePtr = ftell(p_File);
///http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/016_c_ein_ausgabe_funktionen_014.htm#mjff798e62f1469fc3901b349f005d6547
  if(fseek(p_File, 0, SEEK_END) != 0)
    return TU_Bln361095cmnSrcFlSysGetFlSzUse(SeekToEndError);
  *p_fileSizeInB = ftell(p_File);
  ///In order to read from file begin.
  if(fseek(p_File, currFilePtr, SEEK_SET) != 0)
    return TU_Bln361095cmnSrcFlSysGetFlSzUse(SeekToBgnPosError);
  return TU_Bln361095cmnSrcFlSysGetFlSzUse(Success);
}

TU_Bln361095cmnSrcFlSysGetFlSzNmSpcEnd

#endif///include guard
