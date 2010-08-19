//#include "SetExePathAsCurrentDir.h"
#include <windows.h> //for TCHAR
//#include <Windows/LocalLanguageMessageFromErrorCode.h>
#include <global.h> //for WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE
#ifdef __CYGWIN__ //does not have a "tchar.h" shipped.
    #include <Controller/MSVC_adaption/tchar.h> //_tcsrchr()
#else //MSC, MINGW (,...)
    #include <tchar.h> //_tcsrchr()
#endif

//Services get their current working dir set to "%WINDIR%/System32", 
//e.g. C:\WINDOWS\System32, but this is often unwanted because if wanting 
//to read or write to files:
//-this path often has less privileges
//-the configuration file should be chosen from the same dir as where the exe
// resides by default
//So change the path of the current working dir to the path where the 
//executable resides.
DWORD SetExePathAsCurrentDir()
{
  TCHAR artchThisExesPath [ MAX_PATH
    //plus terminating 0 char
    + 1] ;
  DWORD dwModuleFileNameReturn =
    //Cites from
    //http://msdn.microsoft.com/en-us/library/ms683197%28VS.85%29.aspx
    ::GetModuleFileName
      ( 
        //"If this parameter is NULL, GetModuleFileName retrieves the path
        //of the executable file of the current process."
        NULL, 
        //"A pointer to a buffer that receives the fully-qualified path of the
        // module.
        //If the length of the path is less than the size that the
        //nSize parameter specifies, the function succeeds and the path is
        //returned as a null-terminated string.
        //If the length of the path exceeds the size that the nSize parameter specifies, the function succeeds and the string is truncated to nSize characters including the terminating null character.
        //Windows XP/2000:  The string is truncated to nSize characters and
        // is not null terminated."
        artchThisExesPath , 
        //"nSize [in]
        // The size of the lpFilename buffer, in TCHARs."
        MAX_PATH
      ) ;
  //WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(
  //    "Size of path: " << dwModuleFileNameReturn ) ;
  if (//ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/dllproc/base/
      //getmodulefilename.htm:
      //"If the function succeeds, the return value is the length of the 
      //string that is copied to the buffer, in TCHARs."
      //"If the function succeeds, the return value is the length of the
      // string that is copied to the buffer, in characters, not including the
      // terminating null character."
      //"If the function fails, the return value is 0 (zero).
      //To get extended error information, call GetLastError."
      dwModuleFileNameReturn == MAX_PATH ||
      //  == 0
      ! dwModuleFileNameReturn
      )
  {
    //DEBUG("GetModuleFileName failed (%d)\n", GetLastError()); 
    //LOG( 
    //return FALSE;
  }
  else
  {
    TCHAR * ptchLastBackslash = 
      //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.de/dv_vccrt/
      //html/75cf2664-758e-49bb-bf6b-8a139cd474d2.htm:
      //"Scan a string for the last occurrence of a character."
      _tcsrchr(artchThisExesPath,'\\' ) ;
    //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.VisualStudio.v80.de/dv_vccrt/html/
    //75cf2664-758e-49bb-bf6b-8a139cd474d2.htm:
    //"Returns a pointer to the last occurrence of c in str, or 
    //NULL if c is not found."
    if( ptchLastBackslash )
    {
      artchThisExesPath[ //pointer arithmetics: 
          //address of last backslash minus address of first char:
          //If e.g. "C\", the diff is "1"-> string[1] ^= '\0' <=> "C"
          ptchLastBackslash - artchThisExesPath ] = '\0' ;
      if( 
          ::SetCurrentDirectory(
              artchThisExesPath ) 
        )
      {
          //std::cout << "succ set curr path to " << artchThisExesPath 
          //  << "\n" ;
      }
      else
      {
        //WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE( 
        //    "Setting current dir to" << artchThisExesPath << "failed" //\n" 
        //    );
      }
    }
  }
  return dwModuleFileNameReturn ;
}
