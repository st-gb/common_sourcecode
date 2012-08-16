/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
#include <windows.h> //for HMODULE
#include <tchar.h> //for TCHAR

#include <Controller/character_string/stdtstr.hpp>

  std::tstring GetDLLfileName(HMODULE hModule, TCHAR * fileName)
  {
    //  LPSTR lpstrModuleName ;
    //  CHAR ar_strModuleName[100] ;
    //  DWORD dwChars =
    //     GetModuleFileName(
    //     //HINSTANCE
    //     //NULL
    //     GetModuleHandle(NULL)
    ////     ,NULL //LPSTR
    //     , ar_strModuleName
    //     ,99 //DWORD
    //     ) ;
    //see http://stackoverflow.com/questions/846044/how-to-get-the-filename-of-a-dll
    DWORD dwNumChars =
      //http://msdn.microsoft.com/en-us/library/windows/desktop/ms683197%28v=vs.85%29.aspx:
      //"Return value":
      //"length of the string that is copied to the buffer, in characters, not
      //including the terminating null character"
      ::GetModuleFileName(hModule, fileName, MAX_PATH);
    //Point to the end of the string.
    TCHAR * p_tch = fileName + dwNumChars;
    //Go backwards until a backslash is found.
    while( * p_tch != _T('\\') )
      -- p_tch;
    std::tstring std_str( 
      //Increment to start right of '\\'
      ++ p_tch);
    return std_str;
  }
