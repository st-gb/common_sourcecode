///(c) from 2024 by Stefan Gebauer (Computer Science Master from TU Berlin)
///@author Stefan Gebauer (TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
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
 * Sec=SECure: http://www.abbreviations.com/abbreviation/Secure
 * Str=STRing: http://www.abbreviations.com/abbreviation/string
 * Fn/Fun/Func=FUNCtion: http://www.allacronyms.com/function/abbreviated
 * Warn=WARNing: http://www.abbreviations.com/abbreviation/warning */\
 !defined TU_Bln361095compiler__C_andCpp__useSecC_RunTimeStrFnWarn_h
  #define TU_Bln361095compiler__C_andCpp__useSecC_RunTimeStrFnWarn_h

#ifdef _MSC_VER///if MicroSoft Compiler
  ///Sec=SECure: http://www.abbreviations.com/abbreviation/secure
  ///Str=STRing: http://www.abbreviations.com/abbreviation/string
  ///Fn=FuNction: http://www.abbreviations.com/abbreviation/function
  ///Warn=WARNing: http://www.abbreviations.com/abbreviation/warning
  #define TU_Bln361095disableUseSecC_RunTimeStrFnWarn\
    _Pragma("warning(disable:4996)")
  ///Sec=SECure: http://www.abbreviations.com/abbreviation/secure
  ///Str=STRing: http://www.abbreviations.com/abbreviation/string
  ///Fn=FuNction: http://www.abbreviations.com/abbreviation/function
  ///Warn=WARNing: http://www.abbreviations.com/abbreviation/warning
  #define TU_Bln361095enableUseSecC_RunTimeStrFnWarn\
/**http://learn.microsoft.com/en-us/cpp/preprocessor/compiler-warnings-that-are-off-by-default?view=msvc-170
 * "The specified warning (warning_number) is enabled at its default level." */
    _Pragma("warning(default:4996)")
#else
  #define TU_Bln361095enableUseSecC_RunTimeStrFnWarn/**empty*/
  #define TU_Bln361095disableUseSecC_RunTimeStrFnWarn/**empty*/
#endif

#endif//Include guard
