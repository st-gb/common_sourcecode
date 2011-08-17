
#include <preprocessor_macros/logging_preprocessor_macros.h> //DEBUG_COUTN
#include <windef.h> //BYTE

//#ifdef _WIN32_WINNT
//  #undef _WIN32_WINNT
//#endif //_WIN32_WINNT
//#define _WIN32_WINNT 0x0501 //for GetProcessImageFileName(...)
//#include <Psapi.h> //for GetProcessImageFileName(...)

//MinGW 3.4.5 does not have GetProcessImageFileNameA(...) in psapi.h?!, so
//declare it here:
DWORD WINAPI GetProcessImageFileNameA(HANDLE,LPSTR,DWORD);

BYTE GetProcessFileName(DWORD dwProcessID,
    std::string & r_std_strProcessFileName)
{
  BYTE by = 1;
  HANDLE handleProcess =//WINAPI
   ::OpenProcess(
    //see http://msdn.microsoft.com/en-us/library/ms684880%28v=vs.85%29.aspx:
    //0x1000 = PROCESS_QUERY_LIMITED_INFORMATION
    0x1000, //__in  DWORD dwDesiredAccess,
    FALSE, //__in  BOOL bInheritHandle,
    dwProcessID //__in  DWORD dwProcessId
  );
  DEBUG_COUTN("parent process' handle:" << handleProcess)
  //http://msdn.microsoft.com/en-us/library/ms684320(v=vs.85).aspx:
  //"If the function fails, the return value is NULL."
  if( handleProcess)
  {
    TCHAR lpFilename [MAX_PATH ];
    char ar_chFilename [MAX_PATH + 1];

    //Cites from:
    //http://msdn.microsoft.com/en-us/library/ms683217%28v=vs.85%29.aspx:
    //"If the function succeeds, the return value specifies the length of the
    //string copied to the buffer."
    DWORD dw = ::GetProcessImageFileNameA(
      //"The handle must have the PROCESS_QUERY_INFORMATION or PROCESS_QUERY_LIMITED_INFORMATION access right. "
      handleProcess, //__in   HANDLE hProcess,
      ar_chFilename, //__out  LPTSTR lpImageFileName,
      //"The size of the lpImageFileName buffer, in characters."
      MAX_PATH //__in   DWORD nSize
    );
  //        dw =//WINAPI
  //          ::GetModuleFileNameA(
  ////          (HMODULE)
  //          (HINSTANCE) handleProcess, //__in_opt  HMODULE hModule,
  ////          lpFilename, //__out     LPTSTR lpFilename,
  //          ar_chFilename,
  //          MAX_PATH //__in      DWORD nSize
  //        );
    ::CloseHandle(handleProcess);
    if( dw )
    {
        std::string std_str(ar_chFilename);
        std::string::size_type pos = std_str.find_last_of('\\');
        r_std_strProcessFileName = std_str.substr(pos + 1);
        std_str = std_str.substr(pos + 1);
        DEBUG_COUTN("parent process' name:" << ar_chFilename << std_str)
      LOGN( "file name for PID:" << ar_chFilename)
      DEBUG_COUTN("file name for PID:" << ar_chFilename)
      return 0;
    }
    else
    {
//      LOGN( //::GetErrorMessageFromLastErrorCodeA()
//          "GetModuleFileNameA failed:" <<
//          LocalLanguageMessageFromErrorCodeA( ::GetLastError() )
//          )
//      DEBUG_COUTN( //::GetErrorMessageFromLastErrorCodeA()
//        "GetModuleFileNameA failed:" <<
//        LocalLanguageMessageFromErrorCodeA( ::GetLastError() )
//        )
    }
    //QueryFullProcessImageName
  }
  else
  {
//    LOGN( //::GetErrorMessageFromLastErrorCodeA()
//        LocalLanguageMessageFromErrorCodeA( ::GetLastError() )
//        )
//    DEBUG_COUTN("Error opening file name for Process ID:" <<
//        LocalLanguageMessageFromErrorCodeA( ::GetLastError() )
//        )
  }
  return 1;
}
