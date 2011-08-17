/*
 * CallFromService.cpp
 *
 *  Created on: 11.08.2011
 *      Author: Stefan
 */
#include "ServiceBase.hpp"
//GetParentProcessID(...)
#include <Windows/Process/GetParentProcessID/GetParentProcessID.h>
//GetProcessFileName(...)
#include <Windows/Process/GetProcessFileName/GetProcessFileName.h>

//For the following functions it makes only sense to call them from inside
//the service application.

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
