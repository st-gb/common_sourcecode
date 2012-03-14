/*
 * CallFromService.cpp
 *
 *  Created on: 11.08.2011
 *      Author: Stefan
 */
#include "ServiceBase.hpp"

//For the following functions it makes only sense to call them from inside
//the service application.

#if defined(__GNUC__) && __GNUC__ > 3 //GCC 3.4.5 does not have "psapi.a" lib.

//GetParentProcessID(...)
#include <Windows/Process/GetParentProcessID/GetParentProcessID.h>
//GetProcessFileName(...)
#include <Windows/Process/GetProcessFileName/GetProcessFileName.h>

bool ServiceBase::IsStartedAsService()
{
  ULONG_PTR dwParentProcessID = GetParentProcessID();
//  LOGN("parent PID:" << dwParentProcessID)
//  DEBUG_COUTN("parent PID:" << dwParentProcessID)
  if( dwParentProcessID != (ULONG_PTR)-1 )
  {
      std::string std_strParentProcessFileName;

      if( ! GetProcessFileName(dwParentProcessID,
          std_strParentProcessFileName)
        )
        if( std_strParentProcessFileName == "services.exe")
          return true;
  }
  return false;
}
#endif

SERVICE_STATUS_HANDLE ServiceBase::RegSvcCtrlHandlerAndHandleError(
  LPCTSTR lpServiceName,
  LPHANDLER_FUNCTION_EX lpHandlerProc
  )
{
  DWORD dwLastError;
  //ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/dllproc/base/servicemain.htm:
  //"The ServiceMain function should immediately call the
  //RegisterServiceCtrlHandlerEx function to specify a HandlerEx
  //function to handle control requests.
  //s_p_cpucontrolservice->
    //"If the function fails, the return value is zero."
    m_service_status_handle =
    //RegisterServiceCtrlHandler(
      //"GriffinControlService",
      //ServiceCtrlHandler);
      //Use RegisterServiceCtrlHandlerEx  because:
      //http://msdn.microsoft.com/en-us/library/ms810440.aspx:
      //"In addition, HandlerEx [RegisterServiceCtrlHandlerEx(...) is meant?]
      //gets extra messages unique to itself. These messages help a service
      //react appropriately to changes in the hardware configuration or the
      //state of the machine. These service control messages are:
      //[...] SERVICE_CONTROL_POWEREVENT
      //To accept these new messages, the appropriate flags must be submitted using SetServiceStatus. In the SERVICE_STATUS structure, the dwControlsAccepted member should be updated to reflect the desired messages. The bitwise flags are:
      //[...] SERVICE_ACCEPT_POWEREVENT
      //[...] SERVICE_ACCEPT_POWEREVENT is the service equivalent of the WM_POWERBROADCAST message; dwEventType is the power event identifier, and lpEventData is optional data [Code 2]. This is the WPARAM and LPARAM of WM_POWERBROADCAST, respectively."
      //If the function fails, the return value is zero.
      RegSvcCtrlHandlerExAndGetErrMsg(
        //"GriffinControlService",
        //s_p_cpucontrolservice->m_stdtstrProgramName.c_str(),
        lpServiceName,
//        ServiceCtrlHandlerEx,
        lpHandlerProc,
        //http://msdn.microsoft.com/en-us/library/ms685058%28VS.85%29.aspx:
        //"lpContext [in, optional]
        //Any user-defined data. This parameter, which is passed to the
        //handler function, can help identify the service when multiple
        //services share a process."
        (LPVOID) 2,
        //stdstrErrorDescripition
        dwLastError);
  if ( m_service_status_handle
      == (SERVICE_STATUS_HANDLE) 0)
    {
//      WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(
//          "Registering the service control handler failed; "
//          "error code: " << dwLastError );
      std::string std_strErrorDescription;
      ServiceBase::GetErrorDescriptionFromRegSvcCtrlHandlerExErrCode(
          dwLastError, std_strErrorDescription);
//      WRITE_TO_LOG_FILE_AND_STDOUT_NEWLINE(
//          stdstrErrorDescription )
    }
  return m_service_status_handle;
}

SERVICE_STATUS_HANDLE //WINAPI
  ServiceBase::RegSvcCtrlHandlerExAndGetErrMsg(
  //__in
    LPCTSTR lpServiceName,
  //__in
    LPHANDLER_FUNCTION_EX lpHandlerProc,
  //__in_opt
    LPVOID lpContext,
//    std::string & r_stdstrErrorDescription
    DWORD & r_dwErrorCode
  )
{
  m_service_status_handle =
    ::RegisterServiceCtrlHandlerEx ( //"GriffinControlService",
      lpServiceName ,
      lpHandlerProc,
      //http://msdn.microsoft.com/en-us/library/ms685058%28VS.85%29.aspx:
      //"lpContext [in, optional]
      //Any user-defined data. This parameter, which is passed to the
      //handler function, can help identify the service when multiple
      //services share a process."
      lpContext
      );
  //http://msdn.microsoft.com/en-us/library/ms685058%28VS.85%29.aspx:
  //"If the function fails, the return value is zero. To get extended error
  //information, call GetLastError."
  if ( m_service_status_handle == (SERVICE_STATUS_HANDLE) 0 )
  {
    //Get error code for RegisterServiceCtrlHandler(...).
//    DWORD dwLastError = ::GetLastError();
    r_dwErrorCode = ::GetLastError();
  }
  return m_service_status_handle ;
}
