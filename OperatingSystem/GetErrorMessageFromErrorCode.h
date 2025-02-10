/** File:   GetErrorMessageFromErrorCodeA.h
 * Author: s.g.
 * Created on 12. September 2017, 22:08 */

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
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:
 *  http://www.abbreviations.com/abbreviation/Operating+System
 * Msg=MeSsaGe : http://www.abbreviations.com/abbreviation/message */\
 ! defined TU_Bln361095cmnSrc__OpSys__getErrorMsgFromErrorCode_hpp
   #define TU_Bln361095cmnSrc__OpSys__getErrorMsgFromErrorCode_hpp

///C standard library header files:
 #include <string>///std::string,std::wstring

///Stefan Gebauer's(TU Berlin matricul. num. 361095) ~"cmnSrc" repository files:
 #include <preprocessor_macros/Windows_compatible_typedefs.h>///DWORD
 ///TU_Bln361095OpSysNmSpcBgn,TU_Bln361095OpSysNmSpcEnd
 #include "OpSys_ID_prefix.h"

TU_Bln361095OpSysNmSpcBgn

std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode) ;
std::wstring GetErrorMessageFromErrorCodeW(DWORD dwErrorCode) ;

//#ifdef 
//std::string GetErrorMessageFromErrorCodeA(DWORD dwErrorCode )
//{
//  return ::LocalLanguageMessageAndErrorCodeA( dwErrorCode ) ;
//}

TU_Bln361095OpSysNmSpcEnd

#endif///Include guard
