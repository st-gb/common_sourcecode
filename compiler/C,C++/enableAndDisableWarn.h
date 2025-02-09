/**Created on 20.06.2013
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Define on compiler command line,for example for GCC:
 * (see http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :)
 * "gcc -D TU_Bln361095UsePrgmInclGuard"*/
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude: http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD: http://www.abbreviations.com/abbreviation/Guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/source 
 * Warn=WARNing: http://www.abbreviations.com/abbreviation/Warning */\
 !defined TU_Bln361095cmnSrc__compiler__C_andCpp__enableAndDisableWarn_h
  #define TU_Bln361095cmnSrc__compiler__C_andCpp__enableAndDisableWarn_h

/**Adapted from
 * http://www.fluentcpp.com/2019/08/30/how-to-disable-a-warning-in-cpp/ */

#if defined(_MSC_VER)///MicroSoft C compiler
  #define TU_Bln361095disableWarn(warningNumber) __pragma(warning( disable :\
    warningNumber ))
  #define TU_Bln361095enableWarn(warningNumber) __pragma(warning( default:\
    warningNumber ))

  #define TU_Bln361095disablePossibleDataLossOnConversionWarn\
    TU_Bln361095disableWarn(4267)
  #define TU_Bln361095enablePossibleDataLossOnConversionWarn\
    TU_Bln361095enableWarn(4267)
///http://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4189?view=msvc-170
  #define TU_Bln361095disableUnusedVarWarn TU_Bln361095disableWarn(4189)
  #define TU_Bln361095enableUnusedVarWarn TU_Bln361095enableWarn(4189)

#elif defined(__GNUC__) || defined(__clang__)
///http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html

  /** from http://dbp-consulting.com/tutorials/SuppressingGCCWarnings.html */
  #if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
    #define TU_Bln361095GCCdiagStr(s) #s
    #define TU_Bln361095GCCdiagJoinStr(leftStr,rightStr)
      TU_Bln361095GCCdiagStr(leftStr ## rightStr)
    #define TU_Bln361095GCCdiagDoPragma(str) _Pragma (#str)
    #define TU_Bln361095GCCdiagPragma(str)\
      TU_Bln361095GCCdiagDoPragma(GCC diagnostic str)
    #if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406 //GNUC > 4.06
      #define TU_Bln361095disableWarn(warning) \
        TU_Bln361095GCCdiagPragma(push) \
        \
       /*#pragma message "before TU_Bln361095GCCdiagPragma(ignored warning"*/ \
/**TODO Gives GCC error:"pasting "W" and "-" does not give a valid preprocessing
   token"*/ \
        TU_Bln361095GCCdiagPragma(ignored TU_Bln361095GCCdiagJoinStr(-W,warning)
          )
       /*TU_Bln361095GCCdiagPragma(ignored warning)*/
      #define TU_Bln361095enableWarn(warning) TU_Bln361095GCCdiagPragma(pop)
    #else
      #define TU_Bln361095disableWarn(warning) TU_Bln361095GCCdiagPragma(
        ignored TU_Bln361095GCCdiagJoinStr(-W,warning) )
      #define TU_Bln361095enableWarn(warning) TU_Bln361095GCCdiagPragma(warning\
        TU_Bln361095GCCdiagJoinStr(-W,warning))
    #endif
    #define TU_Bln361095GCCdisableWarn(warning) TU_Bln361095disableWarn(
      warning)
    #define TU_Bln361095GCCenableWarn(warning) TU_Bln361095enableWarn(
      warning)
  #endif

  #define TU_Bln361095disablePossibleDataLossOnConversionWarn
  #define TU_Bln361095enablePossibleDataLossOnConversionWarn
  #define TU_Bln361095disableUnusedVarWarn\
    TU_Bln361095disableWarn(unused-variable)
  #define TU_Bln361095enableUnusedVarWarn\
    TU_Bln361095enableWarn(unused-variable)
#else///compiler not handled
  #define TU_Bln361095disableWarn(warning)
  #define TU_Bln361095enableWarn(warning)
  #define TU_Bln361095disablePossibleDataLossOnConversionWarn
  #define TU_Bln361095ensablePossibleDataLossOnConversionWarn
  #define TU_Bln361095disableUnusedVarWarn
  #define TU_Bln361095enableUnusedVarWarn
#endif

#if !defined(__GNUC__) && !defined(__clang__)
  #define TU_Bln361095GCCenableWarn(warning)
  #define TU_Bln361095GCCdisableWarn(warning)
#endif

#endif///include guard
