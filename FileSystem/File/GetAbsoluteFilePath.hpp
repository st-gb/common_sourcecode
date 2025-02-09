/**(c)Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

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
/**Include guard supported by (nearly) all compilers*/\
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * Sys=SYStem:http://www.abbreviations.com/abbreviation/System
 * Abs=ABSolute:http://www.abbreviations.com/abbreviation/Absolute */\
 ! defined TU_Bln361095cmnSrc__FileSys__getAbsPath_h
   #define TU_Bln361095cmnSrc__FileSys__getAbsPath_h

///C standard library header files:
 #include <string> //class std::string

//#include <stdlib.h> //realpath(...)

///Stefan Gebauer's(TU Berlin matricul. num.361095) ~"cmnSrc" repository files:
 ///TU_Bln361095FileSysUse(dirSepChar), TU_Bln361095MicroSoftWindows
 #include <FileSystem/PathSeperatorChar.hpp>
 #ifdef TU_Bln361095MicroSoftWindows
  ///TU_Bln361095FileSysUse(GetAbsPath)
  #include <OperatingSystem/Windows/FileSystem/GetAbsolutePath.hpp>
 #endif
 #ifdef __linux__
  ///FileSystem::GetAbsolutePathA(...)
  #include <OperatingSystem/POSIX/FileSystem/GetAbsolutePath.hpp>
 #endif

TU_Bln361095FileSysNmSpcBgn

inline std::string GetAbsoluteFilePath(
  const std::string & rootPath, 
  const std::string & filePath)
{
  const /*int*/
    /**Use same data type as return value of std::string::rfind(...) to avoid
     * compiler warnings/errors.*/
    std::string::size_type lastPathSepChar = filePath.rfind(
    TU_Bln361095FileSysDef(DirSepChar) );
  std::string absoluteFilePath;
  if( lastPathSepChar != std::string::npos )
  {
    std::string relativeDirPath = filePath.substr(0, lastPathSepChar);
    const /*int*/
      /**Use same data type as return value of std::string::rfind(...) to avoid
       * compiler warnings/errors.*/
      std::string::size_type numOverlappingDirPathChars = rootPath.
      rfind(relativeDirPath);
    if( numOverlappingDirPathChars != std::string::npos )
    {
      absoluteFilePath = rootPath.substr(0, rootPath.length() - 
        numOverlappingDirPathChars);
      absoluteFilePath += filePath;
    }
    else
      return filePath;
  }
  return absoluteFilePath;
}

inline std::wstring GetAbsoluteFilePath(
  const std::wstring & rootPath, 
  const std::wstring & filePath)
{
  const /*int*/
    /**Use same data type as return value of std::wstring::rfind(...) to avoid
     * compiler warnings/errors.*/
    std::wstring::size_type lastPathSepChar = filePath.rfind(
    TU_Bln361095FileSysDef(DirSepCharW) );
  std::wstring absoluteFilePath;
  if( lastPathSepChar != std::string::npos )
  {
    std::wstring relativeDirPath = filePath.substr(0, lastPathSepChar);
    if( relativeDirPath == L"." ) // e.g. "./executable.elf"
    {
      absoluteFilePath = rootPath + filePath.substr(lastPathSepChar, filePath.length() );
    }
    else
    {
      const /*int*/
        /**Use same data type as return value of std::wstring::rfind(...) to
         * avoid compiler warnings/errors.*/
        std::wstring::size_type numOverlappingDirPathChars =
        rootPath.rfind(relativeDirPath);
      if( numOverlappingDirPathChars != std::string::npos )
      {
        absoluteFilePath = rootPath.substr(0, rootPath.length() - 
          numOverlappingDirPathChars);
        absoluteFilePath += filePath;
      }
      else
        return filePath;
    }
  }
  return absoluteFilePath;
}

TU_Bln361095FileSysNmSpcEnd

#endif///Include guard
