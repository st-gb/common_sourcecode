/**(c) Stefan Gebauer,Computer Science Master(from TU Berlin)
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
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:
 *  http://www.abbreviations.com/abbreviation/Operating+System */\
 ! defined TU_Bln361095cmnSrc_OpSys_Win_FileSys_GetAbsPath_h
   #define TU_Bln361095cmnSrc_OpSys_Win_FileSys_GetAbsPath_h

///Standard C(++) library header files:
#include <string>///class std::string

///Microsoft Windows operating system header files:
#include <windows.h>///GetFullPathNameA(...)

///Stefan Gebauer's(TU Berlin matr.#361095)~"common_sourcecode"repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInl
/**TU_Bln361095FileSysDef,TU_Bln361095FileSysNmSpcBgn,
 * TU_Bln361095FileSysNmSpcEnd*/
#include <FileSystem/FileSys_ID_prefix.h>

TU_Bln361095FileSysNmSpcBgn

///"TCHAR" character string version
/**@param getAbsPathFrom must be large enough to hold the absolute path.
 *  Create array with >>MAX_PATH<< elements to be safe. */
TU_Bln361095frcInl DWORD TU_Bln361095FileSysDef(GetAbsPath)(
  const TCHAR getAbsPathFrom[],
  TCHAR strAbsPath[])
{
/**
http://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamea
*/
  return GetFullPathName(
    getAbsPathFrom,///LPCSTR lpFileName
    MAX_PATH,///DWORD nBufferLength
    strAbsPath,///LPSTR lpBuffer
    NULL///LPSTR *lpFilePart
    );
}

///ANSI/ASCII ("char" data type) character string version
/**@param getAbsPathFrom must be large enough to hold the absolute path
 *  Create array with >>MAX_PATH<< elements to be safe. */
TU_Bln361095frcInl DWORD TU_Bln361095FileSysDef(GetAbsPathA)(
  const char getAbsPathFrom [],
  char strAbsPath[])
{
/**
http://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamea
*/
  return GetFullPathNameA(
    getAbsPathFrom,///LPCSTR lpFileName
    MAX_PATH,///DWORD nBufferLength
    strAbsPath,///LPSTR lpBuffer
    NULL///LPSTR *lpFilePart
    );
}

#ifdef __cplusplus///uses std::string->C++

/**@brief ANSI version for getting absolute file system path
 * @param strRelOrAbsPath get absolute path from this path */
TU_Bln361095frcInl DWORD
  ///Abs=ABSolute: http://www.abbreviations.com/abbreviation/Absolute
  GetAbsPathA(const char strRelOrAbsPath[], std::string & stdstrAbsFilePath)
{
/**
http://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamea
 */
  DWORD retVal = GetFullPathNameA(strRelOrAbsPath,
    0,///lpBuffer size in number of characters 
    NULL,///lpBuffer
    NULL);
/**
http://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfullpathnamea
 * : "If the lpBuffer buffer is too small to contain the path, the return value
 * is the size, in TCHARs, of the buffer that is required to hold the path and
 * the terminating null character.
 * 
 * If the function fails for any other reason, the return value is zero." */
  if(retVal > 0)
  {
    const DWORD numChars = retVal +1;
    /**Create array on heap (and not on stack with array size known at runtime)
     * to avoid compile error C2131 in Microsoft Visual Studio (at least in
     * version 17 from year 2022). */
    char * strAbsPath = (char*)malloc(numChars);
    retVal = GetFullPathNameA(strRelOrAbsPath, numChars, strAbsPath, NULL);
    stdstrAbsFilePath = strAbsPath;
    free(strAbsPath);
  }
  return retVal;
}

#endif///#ifdef __cplusplus

TU_Bln361095FileSysNmSpcEnd

#endif///include guard
