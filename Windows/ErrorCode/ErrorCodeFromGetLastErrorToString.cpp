/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
//Wenn der Compiler-Fehler "C1010" auftritt, dann liegt das bestimmt an der
//Befehlszeilenoption /Yu (Verwenden einer vorkompilierten Header-Datei)
//siehe Menü "Projekt" Menüpunkt "Einstellungen..." Karteireiter "C/C++"
//Textbox "Projekt Optionen" Befehlszeilenoption "Yu" (in der Textbox unten,
//also eventuell herunterscrollen) dann entweder die direkt hinter "Yu"
//angegebene Datei einbinden ("#include ") oder die Befehlszeilenoption "/Yu"
//entfernen.
//#include "stdafx.h"
#include "ErrorCodeFromGetLastErrorToString.h"
#include <string> //class std::string
//#ifndef _MSC_VER
  #include <windows.h> //for ::FormatMessage(...)
  #include <winnt.h> //for MAKELANGID
//#include <Controller/tchar_conversion.h> //GetCharPointer(...)
#include <Controller/character_string/stdtstr.hpp> //GetStdString(...)
//#endif

//Diese Funktion liefert die zum DWORD-(unsigned long-) Wert der Windows-API-
//Funktion "DWORD GetLastError(void)" korrespondierende Fehlermeldung als Text
//in der Standard-Sprache der laufenden Windows-Sitzung.
//CString 
//std::string 
DWORD GetLastErrorMessageString(
  DWORD dwErrorCodeConformToGetLastError ,
  std::string & strErrorMessage
  )
{
  DWORD dwRet = ERROR_SUCCESS ;
	//CString strErrorMessage;
  //std::string strErrorMessage;
	LPVOID lpMsgBuf = NULL;
  //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/debug/base/
	// formatmessage.htm:
  //"If the function fails, the return value is zero. 
  //To get extended error information, call GetLastError."
  if( ! ::FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwErrorCodeConformToGetLastError,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
      (LPTSTR) & lpMsgBuf,
      0,
      NULL
      )
    )
    dwRet = ::GetLastError() ;
  else
	  //strErrorMessage = (LPCTSTR)lpMsgBuf;
    strErrorMessage = //std::string( GetCharPointer( ((LPCTSTR) lpMsgBuf) ) );
      GetStdString( (LPCTSTR) lpMsgBuf ) ; 

	if( lpMsgBuf != NULL )
    ::LocalFree(lpMsgBuf);

	return //strErrorMessage;
    dwRet ;
}

//Diese Funktion liefert die zum DWORD-(unsigned long-) Wert der Windows-API-
//Funktion "DWORD GetLastError(void)" korrespondierende Fehlermeldung als Text
//in der Standard-Sprache der laufenden Windows-Sitzung.
//CString
//std::string
DWORD GetLastErrorMessageString(
  DWORD dwErrorCodeConformToGetLastError ,
  std::wstring & r_std_wstrErrorMessage
  )
{
  DWORD dwRet = ERROR_SUCCESS ;
  //CString strErrorMessage;
  //std::string strErrorMessage;
  LPVOID lpMsgBuf = NULL;
  //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/debug/base/
  // formatmessage.htm:
  //"If the function fails, the return value is zero.
  //To get extended error information, call GetLastError."
  if( ! ::FormatMessageW(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, //lpSource
      dwErrorCodeConformToGetLastError,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
      (LPTSTR) & lpMsgBuf,
      0, //nSize
      NULL //Arguments
      )
    )
    dwRet = ::GetLastError() ;
  else
    //strErrorMessage = (LPCTSTR)lpMsgBuf;
    r_std_wstrErrorMessage = std::wstring( //(LPCWSTR)
        (wchar_t *) lpMsgBuf );

  if( lpMsgBuf != NULL )
    ::LocalFree(lpMsgBuf);

  return //strErrorMessage;
    dwRet ;
}

namespace OperatingSystem
{
//  inline DWORD GetLastErrorCode()
//  {
//    return ::GetLastError() ;
//  }
}

std::string GetErrorMessageFromErrorCodeA( DWORD dwErrorCode )
{
  std::string strErrorMessage ;
  GetLastErrorMessageString(
    dwErrorCode ,
    strErrorMessage
    ) ;
  return strErrorMessage ;
}
std::wstring GetErrorMessageFromErrorCodeW( DWORD dwErrorCode )
{
  std::wstring std_wstrErrorMessage ;
  GetLastErrorMessageString(
    dwErrorCode ,
    std_wstrErrorMessage
    ) ;
  return std_wstrErrorMessage ;
}

std::string GetLastErrorMessageString(
  DWORD dwErrorCodeConformToGetLastError
  //std::string & strErrorMessage
  )
{
  std::string strErrorMessage ;
  GetLastErrorMessageString(
    dwErrorCodeConformToGetLastError ,
    strErrorMessage 
    ) ;
  return strErrorMessage ;
}

//#define GetErrorMessageFromErrorCodeA GetLastErrorMessageString ;
