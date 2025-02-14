/*'File name comes from:
 *  Curr=CURRent:
 *  Dir=DIRectory
 * Created on: Dec 30, 2010(Berlin, Germany time zone)
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095) */

///Include guard, see http://en.wikipedia.org/wiki/Include_guard :

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
/**Bln=BerLiN: https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 *  Curr=CURRent:
 *  Dir=DIRectory */\
 ! defined TU_Bln361095cmnSrc__FileSys__GetCurrWorkngDir_hpp
   #define TU_Bln361095cmnSrc__FileSys__GetCurrWorkngDir_hpp

//#include <string> //class std::string

///Stefan Gebauer's(TU Berlin matricul. num. 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095MicrosoftWindows
 #include <OperatingSystem/Windows/MicrosoftWindows.h>

#ifdef __unix__
//namespace Unixoid
//{
//	GetCurrentWorkingDir(std::string & r_stdstr ) ;
//}
#define Unixoid OperatingSystem
#endif

//namespace /*CurrentProcess*/ OperatingSystem
//{
//void GetCurrentWorkingDir(std::string & r_stdstr ) ;
//}

#if defined(__unix__) //Linux, Android NDK
//  #define OperatingSystem Linux
  #include <OperatingSystem/Linux/FileSystem/GetCurrentWorkingDir/GetCurrentWorkingDir.hpp>
//  #undef OperatingSystem
#endif
#ifdef TU_Bln361095MicrosoftWindows
  //#define Windows OperatingSystem
  #include <OperatingSystem/Windows/FileSystem/GetCurrentDirectory/GetCurrentDirectory.hpp>

#endif

//namespace /*CurrentProcess*/ OperatingSystem
//{
//  inline void GetCurrentWorkingDirA_inl(std::string & r_stdstr )
//  {
//#if defined(__unix__) //Linux, Android NDK
//    Linux_::GetCurrentWorkingDirA_inl(r_stdstr);
//#endif
//#ifdef _WIN32
//	Windows::GetCurrentWorkingDirA_inl(r_stdstr);
//#endif
//  }
//}

//void SetCurrentWorkingDir(const std::string & r_stdstr ) ;

#endif///include guard
