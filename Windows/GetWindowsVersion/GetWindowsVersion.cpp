#include "GetWindowsVersion.h"

//from http://support.microsoft.com/kb/307394
#include "stdafx.h"
#include <Windows.h>
#ifdef __CYGWIN__ //does not have a "tchar.h" shipped.
    #include <Controller/MSVC_adaption/tchar.h> //_tcsrchr()
#else //MSC, MINGW (,...)
    #include <tchar.h> ////for _T(...), _tcscmp(...)
#endif
//#include <Controller/tchar_conversion.h> //GetCharPointer(...)
//#include <Controller/character_string/stdtstr.hpp> //GetCharPointer(...)
//#include <string.h>

//#using <mscorlib.dll>

//using namespace System;

//// This is the entry point for this application
//#ifdef _UNICODE
//int wmain(void)
//#else
//int main(void)
//#endif
std::string GetWindowsVersion(DWORD & r_dwMajorVersion ,DWORD & r_dwMinorVersion )
{
  std::string strVersion ;
  OSVERSIONINFO osversioninfo ;

  //http://msdn.microsoft.com/en-us/library/ms724451%28VS.85%29.aspx:
  //setting the dwOSVersionInfoSize is needed, else GetVersionEx() failed
  //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/sysinfo/base/
  // getversionex.htm:
  osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  //get OperatingSystem info from the system namespace
  if( ::GetVersionEx(
      & osversioninfo   
      )
    )
  {
    r_dwMajorVersion = osversioninfo.dwMajorVersion ;
    r_dwMinorVersion = osversioninfo.dwMinorVersion ;
    //is the platform win9x or NT
    switch( osversioninfo.dwPlatformId )
    {
      //platform is win9x
      case VER_PLATFORM_WIN32_WINDOWS :
        switch (osversioninfo.dwMinorVersion )
        {
          case 0:
             strVersion = "Windows 95" ;
          break;
          case 10:
            if( //std::string( GetCharPointer(
              //osversioninfo.szCSDVersion ) ) == "2222A" )
//              GetStdString(osversioninfo.szCSDVersion ) == "2222A"

              //http://msdn.microsoft.com/en-us/library/e0z9k731%28VS.80%29.aspx:
              //0: string1 identical to string2
              //Strings match.
              ! _tcscmp(osversioninfo.szCSDVersion, _T("2222A" ) )
              )
             strVersion = "Windows 98 Second Edition" ;
          else
             strVersion = "Windows 98" ;
          break;
          case  90:
             strVersion = "Windows ME" ;
          break;
        }
        break;
      //platform is NT
      //http://msdn.microsoft.com/en-us/library/ms724834%28v=VS.85%29.aspx:
      //"The operating system is Windows Server 2008, Windows Vista, Windows
      //Server 2003, Windows XP, or Windows 2000."
      case VER_PLATFORM_WIN32_NT :
        switch(osversioninfo.dwMajorVersion )
        {
           case 3:
              strVersion = "Windows NT 3.51" ;
             break;
           case 4:
              strVersion = "Windows NT 4.0" ;
             break;
           case 5:
             if ( osversioninfo.dwMinorVersion == 0 )
                strVersion = "Windows 2000" ;
             else
                strVersion = "Windows XP" ;
             break;
           case 6:
             switch( osversioninfo.dwMinorVersion )
             {
             case 0:
               strVersion = "Windows Vista" ;
               break;
             case 1:
               strVersion = "Windows 7" ;
               break;
             }
             break;
        }
        break;
    } //switch( osversioninfo.dwPlatformId )
  }
  return strVersion ;
}
