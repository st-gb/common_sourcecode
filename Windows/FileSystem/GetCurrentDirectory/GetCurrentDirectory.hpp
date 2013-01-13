/*
 * GetCurrentDirectory.hpp
 *
 *  Created on: 03.07.2012
 *      Author: Stefan
 */

#ifndef GETCURRENTDIRECTORY_HPP_
#define GETCURRENTDIRECTORY_HPP_

#include <windows.h> //::GetCurrentDirectory(...)

namespace Windows
{
  unsigned GetCurrentDirectory(std::tstring & r_std_tstrCurrentDirectory)
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
}

#endif /* GETCURRENTDIRECTORY_HPP_ */