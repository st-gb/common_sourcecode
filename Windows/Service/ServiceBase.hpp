#pragma once

//Must be included BEFORE Windows-specific inlcudes (else: comp. errors like:
//C:/MinGW/bin/../lib/gcc/mingw32/3.4.5/../../../../include/c++/3.4.5/bits/
// istream.tcc:1164: error: expected primary-expression before '.' token

#include <string> //for std::string
#include <windows.h> //BOOL
#include <winsvc.h> //LPHANDLER_FUNCTION_EX
//For THREAD_FUNCTION_CALLING_CONVENTION.
#include <Controller/multithread/thread_function_calling_convention.h>
//#include <specstrings.h> // "__in" etc.

////for ::GetErrorMessageFromErrorCodeA(DWORD)
//#include <Controller/GetErrorMessageFromLastErrorCode.hpp>
//For ::GetLastErrorMessageString(DWORD ,std::wstring)
#include <Windows/ErrorCode/ErrorCodeFromGetLastErrorToString.h>

typedef unsigned long DWORD;

class ConnectToSCMerror
{
public:
  DWORD m_dwErrorCode ;
  ConnectToSCMerror(DWORD dwErrorCode) { m_dwErrorCode = dwErrorCode ; }
  void GetErrorMessage(std::wstring & std_wstrErrorMessage) const
  {
    ::GetLastErrorMessageString(m_dwErrorCode, std_wstrErrorMessage);
    if( std_wstrErrorMessage == L"" )
      std_wstrErrorMessage = L"no error message available";
  }
};

//To avoid replacing "StartService" to "StartServiceA" / "StartServiceW" in
//"winsvc.h"
#ifdef StartService
  #undef StartService
#endif

class ServiceBase
{
protected:
  SERVICE_STATUS_HANDLE m_service_status_handle ;
public:
  //Declare avoid g++ warning "Class 'ServiceBase' has virtual method
  //'SetServiceStatus' but non-virtual destructor".
  virtual ~ServiceBase() {};
  //static
     SERVICE_STATUS m_servicestatus;
  enum errorCodes
  {
    NoError = 0 ,
    OpenSCManagerFailed,
    OpenServiceFailed,
    DeleteServiceFailed,
    GetModuleFileNameFailed
  };
  static bool CanStartService() ;
  static DWORD ContinueService(
   const TCHAR * tchServiceName
   ) ;
  static DWORD CreateService(
    const TCHAR * tchServiceName
    , BYTE & r_byErrorPlace
    ) ;
  static DWORD CreateService(
    SC_HANDLE & r_schService 
    , const TCHAR * tchServiceName
    , TCHAR * tchPathcToServiceExe
    , SC_HANDLE schSCManager
    ) ;
  //return: 0 = success
  static //DWORD
    BYTE DeleteService(
      const TCHAR * tchServiceName
      , DWORD & dwErrorCodeFor1stError
   ) ;
  static void GetErrorDescriptionFromStartServiceCtrlDispatcherErrCode(
    DWORD dwLastError ,
    std::string & r_stdstrErrorDescription
    ) ;
  static void GetErrorDescriptionFromRegSvcCtrlHandlerExErrCode(
    DWORD dwLastError ,
    std::string & r_stdstrErrorDescription
    ) ;
  static void GetErrorDescriptionFromCreateServiceErrCode(
    DWORD dwLastError ,
    std::string & r_stdstrErrorDescription
    ) ;
  static void GetErrorDescriptionFromOpenServiceErrCode(
    DWORD dwLastError ,
    std::string & r_stdstrErrorDescription
    ) ;
#if defined(__GNUC__) && __GNUC__ > 3 //GCC 3.4.5 does not have "psapi.a" lib.
  static bool IsStartedAsService();
#endif
  static DWORD PauseService(
   const TCHAR * tchServiceName
   , std::string & r_stdstrMsg
   ) ;
  static void GetPossibleSolution(
    DWORD dwWinError ,
    const TCHAR * tchServiceName
    //use as reference param and do not return because so it is not copied
    //->faster
    , std::string & r_stdstrPossibleSolution
    ) ;
  //Needs to be "virtual" in order to use a possible sublass's overridden
  //implementation.
  virtual SERVICE_STATUS_HANDLE RegSvcCtrlHandlerAndHandleError(
    LPCTSTR lpServiceName,
    LPHANDLER_FUNCTION_EX lpHandlerProc);
  //from http://msdn.microsoft.com/en-us/library/ms685058%28VS.85%29.aspx:
  SERVICE_STATUS_HANDLE //WINAPI
    RegSvcCtrlHandlerExAndGetErrMsg(
    //__in
      LPCTSTR lpServiceName,
    //__in
      LPHANDLER_FUNCTION_EX lpHandlerProc,
    //__in_opt
      LPVOID lpContext ,
//      std::string & r_stdstrErrorDescription
      DWORD & r_dwErrorCode
    );
  void SetInitialServiceStatusAttributeValues(
    DWORD dwServiceType,
    DWORD dwControlsAccepted
    );
  //Needs to be "virtual" in order to use a possible sublass's overridden
  //implementation.
  virtual void SetServiceStatus();
//  SERVICE_STATUS_HANDLE //WINAPI
//    RegSvcCtrlHandlerExAndGetErrMsg(
//    //__in
//      LPCTSTR lpServiceName,
//    //__in_opt
//      LPVOID lpContext ,
////      std::string & r_stdstrErrorDescription
//      DWORD & r_dwErrorCode
//    );
//  //from http://msdn.microsoft.com/en-us/library/ms683241%28v=VS.85%29.aspx:
//  //overwrite in subclasses
//  //MUST be static (=without "this" pointer ) because this is a
//  //callback function from Windows API.
//  static virtual DWORD WINAPI ServiceCtrlHandlerEx(
//    __in  DWORD dwControl,
//    __in  DWORD dwEventType,
//    __in  LPVOID lpEventData,
//    __in  LPVOID lpContext
//    ) { return 0 ; } ;
  static DWORD Start(
    LPCTSTR lpServiceName ) ;
  static DWORD Start(
    SC_HANDLE schSCManager
    , LPCTSTR lpServiceName ) ;
  static DWORD THREAD_FUNCTION_CALLING_CONVENTION
    StartServiceCtrlDispatcher_static(void * p_v);
  static DWORD Stop(
    LPCTSTR lpServiceName ) ;
  static DWORD Stop(
    SC_HANDLE schSCManager
    , LPCTSTR lpServiceName ) ;
};
