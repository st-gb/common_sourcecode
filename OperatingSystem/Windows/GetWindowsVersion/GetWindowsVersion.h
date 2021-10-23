#pragma once

#include <string>
#include <Windows.h> //for DWORD

std::string GetWindowsVersion(DWORD & dwMajor ,DWORD & dwMinor) ;

/** Windows changed API beginning with Windows XP. So this function is handy.*/
inline bool isWindowsXP(){
  OSVERSIONINFO osversioninfo ;
  osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if( ::GetVersionEx(& osversioninfo) &&   
    osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT &&
    osversioninfo.dwMajorVersion == 5 && 
    osversioninfo.dwMinorVersion > 0)
    return true;
  return false;
}

/** Windows changed API beginning with Windows Vista, e.g. in power profile
 * access or  performance monitoring. So this function is handy. */
inline bool atLeastWinVista()
{
  OSVERSIONINFO osversioninfo ;
  osversioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if( ::GetVersionEx(& osversioninfo) &&   
    osversioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT &&
    osversioninfo.dwMajorVersion > 5 && 
    osversioninfo.dwMinorVersion >= 0)
    return true;
  return false;
}
