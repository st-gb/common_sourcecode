/**(c) Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
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
/**Bln=Berlin:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * Sys=SYStem:http://www.abbreviations.com/abbreviation/system */\
 ! defined TU_Bln361095cmnSrc__FileSys__FileException_hpp
   #define TU_Bln361095cmnSrc__FileSys__FileException_hpp

///Standard C library header files:
 #include <string.h>///strlen(...)

///**From Microsoft Visual Studio or from Stefan Gebauer's(TU Berlin matric.
// * number 361095) ~"cmnSrc" repository:*/
// #include <tchar.h>

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 #include <dataType/charStr/strTermChar.h>///TU_Bln361095numCharsForStrTermChar
 ///TU_Bln361095FileSysNmSpcBgn, TU_Bln361095FileSysNmSpcEnd
 #include <FileSystem/FileSys_ID_prefix.h>

///for DWORD:
 #ifdef _MSC_VER///if MicroSoft Compiler
   #include /*<minwindef.h>*/<windows.h>///DWORD
 #else
  ///Stefan Gebauer's(TU Berlin matricul. number 361095) ~"cmnSrc" repository:
  #include <preprocessor_macros/Windows_compatible_typedefs.h>///DWORD
 #endif

TU_Bln361095FileSysNmSpcBgn

class FileException
{
protected:
	//std::tstring str;
	//  TCHAR * m_filePath;
	//TODO why not use a std::wstring here?->deleting the array in the destructor
	// would be unneccessary
	wchar_t * m_filePath;
	//  std::wstring m_filePath;
	DWORD m_operatingSystemErrorCode;
public:
  void cpyWchars(const wchar_t chFilePath []){
    const /*int*/
      ///Use same data type as in wcslen(...) to avoid compiler warnings/errors.
      size_t
      ///chr=CHaRacter:http://www.abbreviations.com/abbreviation/character
      chrArrSize = wcslen(chFilePath);
    m_filePath = new wchar_t[chrArrSize + TU_Bln361095numCharsForStrTermChar];
    wcscpy(m_filePath, chFilePath);
  }
  
  FileException() : m_filePath(0), m_operatingSystemErrorCode(0) { }
  
  FileException(const wchar_t * const chFilePath)
    : m_operatingSystemErrorCode(0)
//    , m_filePath(chFilePath)
  {
    cpyWchars(chFilePath);
  }
  
  FileException(const char * const chFilePath)
    : m_operatingSystemErrorCode(0)
  {
    const /*unsigned int*/
      ///Use same data type as in strlen(...) to avoid compiler warnings/errors.
      size_t
      ///chr=CHaRacter:http://www.abbreviations.com/abbreviation/character
      chrArrSize = strlen(chFilePath);
    m_filePath = new wchar_t[chrArrSize + TU_Bln361095numCharsForStrTermChar];
//    _tcscpy(m_filePath, chFilePath);
    for( unsigned int index = 0; index < chrArrSize; index ++ )
    {
      m_filePath[index] = chFilePath[index];
    }
    m_filePath[chrArrSize] = L'\0';
    //str = ch;
  }

  ///Also called when doing a "throw" with an object of this class.
  FileException(const FileException & fe)
  {
    cpyWchars(fe.m_filePath);
    m_operatingSystemErrorCode = fe.m_operatingSystemErrorCode;
  }

  /** Called when created on stack a´when leaving block or at end of catch(...)
   *  with a FileException-based class.*/
  ~FileException()
  {
    if( m_filePath){
      delete [] m_filePath;
      m_filePath = NULL;
    }
  }

  //TODO?
//  inline const std::string GetErrorMessageA() const
//  {
//
//  }
  
  wchar_t * GetFilePath() const
  {
    return m_filePath;
  }
};

TU_Bln361095FileSysNmSpcEnd

#endif///Include guard
