/**File name "cmdLneArgs" comes from:CoMmanD LiNE ARGumentS
 * (c) from 09.02.2013 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPeratingSYStem:
 *  http://www.abbreviations.com/abbreviation/operating%20system
 * cmd=CoMmanD: http://www.abbreviations.com/abbreviation/command
 * Lne=LiNE
 * Args=ARGUmentS: http://www.abbreviations.com/abbreviation/argument */\
 ! defined TU_Bln361095cmnSrc__OpSys__Process__parseCmdLneArgs_h
   #define TU_Bln361095cmnSrc__OpSys__Process__parseCmdLneArgs_h

/**TU_Bln361095OpSysProcessCmdLneArgsDef,
 * TU_Bln361095OpSysProcessCmdLneArgsNmSpc,
 * TU_Bln361095OpSysProcessCmdLneArgsNmSpcBgn,
 * TU_Bln361095OpSysProcessCmdLneArgsNmSpcEnd */
#include "../cmdLineArgs.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
 /**Def=definition: http://www.abbreviations.com/abbreviation/definition
  * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysProcessCmdLneArgsParseDef(suffix) suffix
    /**Nm=name: http://www.abbreviations.com/abbreviation/name
     * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095OpSysProcessCmdLneArgsParseNmSpc\
    TU_Bln361095OpSysProcessCmdLneArgsNmSpc ::\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace >>this #define'd namespace<<" */\
    Parse
  ///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysProcessCmdLneArgsParseNmSpcBgn\
    TU_Bln361095OpSysProcessCmdLneArgsNmSpcBgn namespace Parse{
  #define TU_Bln361095OpSysProcessCmdLneArgsParseNmSpcEnd\
    TU_Bln361095OpSysProcessCmdLneArgsNmSpcEnd }
  #define TU_Bln361095OpSysProcessCmdLneArgsParseUse(suffix)\
    TU_Bln361095OpSysProcessCmdLneArgsParseNmSpc :: suffix
#else///C compiler
  #define TU_Bln361095OpSysProcessCmdLneArgsParseDef(suffix)\
    TU_Bln361095OpSysProcessCmdLneArgsDef(Parse##suffix)
  #define TU_Bln361095OpSysProcessCmdLneArgsParseNmSpc/**empty*/
  #define TU_Bln361095OpSysProcessCmdLneArgsParseNmSpcBgn/**empty*/
  #define TU_Bln361095OpSysProcessCmdLneArgsParseNmSpcEnd/**empty*/
  #define TU_Bln361095OpSysProcessCmdLneArgsParseUse(suffix)\
    TU_Bln361095OpSysProcessCmdLneArgsParseDef(suffix)
#endif

TU_Bln361095OpSysProcessCmdLneArgsParseNmSpcBgn

enum TU_Bln361095OpSysProcessCmdLneArgsParseDef(Rslt) {
  TU_Bln361095OpSysProcessCmdLneArgsParseDef(Sccss) = 0,
  TU_Bln361095OpSysProcessCmdLneArgsParseDef(ArgsUnset),
  TU_Bln361095OpSysProcessCmdLneArgsParseDef(Error)
};

TU_Bln361095OpSysProcessCmdLneArgsParseNmSpcEnd

#endif///include guard