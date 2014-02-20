/*
 * GetCurrentDirectory.hpp
 *
 *  Created on: 03.07.2012
 *      Author: Stefan
 */

#ifndef GETCURRENTDIRECTORY_HPP_
#define GETCURRENTDIRECTORY_HPP_

#include <windows.h> //::GetCurrentDirectory(...)
#include <Controller/character_string/stdtstr.hpp>

namespace Windows
{
  inline unsigned GetCurrentWorkingDir_Inl(std::tstring & r_std_tstrCurrentDirectory)
  {
    unsigned retVal = 1;
    DWORD dw =
    //http://msdn.microsoft.com/en-us/library/aa364934(VS.85).aspx:
    //If the buffer that is pointed to by lpBuffer is not large
    //enough, the return value specifies the required size of
    //the buffer, in characters, including the null-terminating
    //character.
    ::GetCurrentDirectory(
      //__in   DWORD nBufferLength,
      0 ,
      //__out  LPTSTR lpBuffer
      NULL
    );
    LPTSTR lptstrCurrentDirectory = new
      TCHAR[dw] ;
    if(
      //If the function succeeds, the return value specifies the
      //number of characters that are written to the buffer, not
      //including the terminating null character.
      ::GetCurrentDirectory(
        //The length of the buffer for the current directory string,
        //in TCHARs. The buffer length must include room for a
        //terminating null character.
        dw
        , lptstrCurrentDirectory
        ) == (dw - 1)
      )
    {
      r_std_tstrCurrentDirectory = std::tstring(lptstrCurrentDirectory);
      retVal = 0;
    }
    if( lptstrCurrentDirectory )
      delete [] lptstrCurrentDirectory ;
    return retVal;
  }

  inline unsigned GetCurrentWorkingDirA_inl(std::string & r_std_strCurrentDirectory)
  {
    unsigned retVal = 1;
    DWORD dw =
    //http://msdn.microsoft.com/en-us/library/aa364934(VS.85).aspx:
    //If the buffer that is pointed to by lpBuffer is not large
    //enough, the return value specifies the required size of
    //the buffer, in characters, including the null-terminating
    //character.
    ::GetCurrentDirectoryA(
      //__in   DWORD nBufferLength,
      0 ,
      //__out  LPTSTR lpBuffer
      NULL
    );
    LPSTR lpstrCurrentDirectory = new
      CHAR[dw] ;
    if(
      //If the function succeeds, the return value specifies the
      //number of characters that are written to the buffer, not
      //including the terminating null character.
      ::GetCurrentDirectoryA(
        //The length of the buffer for the current directory string,
        //in TCHARs. The buffer length must include room for a
        //terminating null character.
        dw
        , lpstrCurrentDirectory
        ) == (dw - 1)
      )
    {
      r_std_strCurrentDirectory = std::string(lpstrCurrentDirectory);
      retVal = 0;
    }
    if( lpstrCurrentDirectory )
      delete [] lpstrCurrentDirectory ;
    return retVal;
  }

  /** Must be declared "inline", else multiple definitions of this function
   *  are possible -> error when linking. */
  inline unsigned GetCurrentWorkingDir(std::tstring & r_std_tstrCurrentDirectory)
  {
    return GetCurrentWorkingDir_Inl(r_std_tstrCurrentDirectory);
  }

  /** Must be declared "inline", else multiple definitions of this function
   *  are possible -> error when linking. */
  inline unsigned GetCurrentWorkingDirA(std::string & r_std_strCurrentDirectory)
  {
    return GetCurrentWorkingDirA_inl(r_std_strCurrentDirectory);
  }
}

#endif /* GETCURRENTDIRECTORY_HPP_ */
