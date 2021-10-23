/** PDH_CPUcoreUsageGetter.cpp
 *  Created on: Apr 26, 2010
 *  Author: Stefan Gebauer, M.Sc. Comp.Sc. */

//#include "StdAfx.h"
//#include <iosfwd>

///C(++) standard header files:
#include <string> //std::wstring
#include <stdlib.h> //_itow(...)
#include <sstream>///std::osstringstream
#include <wchar.h>///wcscmp(...)

///MS Windows API header files:
#include <windows.h> //FormatMessageW(...)
#include <winperf.h>///PERF_DETAIL_NOVICE
#include <pdhmsg.h>///PDH error codes

///Stefan Gebauer's common_sourcecode repository files:
#include <compiler/GCC/avoid_write_strings_warning.h>///CAST_TO_WCHAR_POINTER
#include <hardware/CPU/fastest_data_type.h>///fastestUnsignedDataType
///class CPUcoreUsageException
#include <OperatingSystem/CPUcoreUsageException.hpp>
///isWindowsXP(), atLeastWinVista()
#include <OperatingSystem/Windows/GetWindowsVersion/GetWindowsVersion.h>
#include <preprocessor_macros/logging_preprocessor_macros.h>
#ifdef _DEBUG
  #include <Windows/Process/GetCurrentProcessExeFileNameWithoutDirs/GetCurrentProcessExeFileNameWithoutDirs.hpp>
#endif
/** This file includes "pdh.h" from Microsoft. Include it AFTER including the
 * g++ include, else build errors with istream/ string. */
#include "PDH_CPUcoreUsageGetter.hpp"

//#ifndef _MSC_VER
//  #include <Windows_compatible_typedefs.h>
//#endif //#ifndef _MSC_VER
//#include <string>
//#include <exception>
//#include <stdexcept>
//#include <Pdh.h>

//TODO the _DEBUG define is not visible here although it was declared as an
//argument for the compiler
//#define _DEBUG

//from http://msdn.microsoft.com/en-us/library/aa373046%28v=VS.85%29.aspx:
BYTE PDH_CPUcoreUsageGetter::GetPDHerrorCodeString(
  DWORD dwErrorCode,std::wstring & wstr )
{
  //std::wstring wstr ;
//  HANDLE hPdhLibrary = NULL;
    LPWSTR pMessage = NULL;
    DWORD_PTR pArgs[] = { (DWORD_PTR)L"<collectionname>" };
    //DWORD dwErrorCode = PDH_PLA_ERROR_ALREADY_EXISTS;

//    hPdhLibrary = LoadLibraryW(L"pdh.dll");
    if ( NULL == //hPdhLibrary
        m_hinstancePDH_DLL )
    {
        DEBUGN( "LoadLibrary failed with " << GetLastError() );
        return 0;
    }

    // Use the arguments array if the message contains insertion points, or you
    // can use FORMAT_MESSAGE_IGNORE_INSERTS to ignore the insertion points.
    if ( ! ::FormatMessageW(
      FORMAT_MESSAGE_FROM_HMODULE |
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        /*FORMAT_MESSAGE_IGNORE_INSERTS |*/
        FORMAT_MESSAGE_ARGUMENT_ARRAY,
//       hPdhLibrary,
      m_hinstancePDH_DLL ,
      dwErrorCode,
      0,
      (LPWSTR)&pMessage,
      0,
      //NULL))
      (va_list*)pArgs)
      )
    {
        DEBUGWN_WSPRINTF( L"Format message failed with error code %u",
          ::GetLastError() );
        return 0;
    }

    DEBUGWN_WSPRINTF( L"Formatted message: %ls", pMessage);
    wstr = std::wstring(pMessage) ;
    ::LocalFree(pMessage);
    return 1 ;
}

/** @return 0=success */
BYTE PDH_CPUcoreUsageGetter::InitPDH_DLLaccess()
{
  DEBUGN("PDH_CPUcoreUsageGetter::InitPDH_DLLaccess()" )
  m_hinstancePDH_DLL =
    //If the function fails, the return value is NULL.
    ::LoadLibraryA( "pdh.dll" //LPCSTR / char *
      );
  if( m_hinstancePDH_DLL )
  {
    DEBUGN("pdh.dll loaded")
    AssignDLLfunctionPointers() ;
    //StartPerfCounting() ;
    return 0;
  }
  else
  {
    DEBUGN("could not load pdh.dll")
//    throw std::exception() ;
    //When thrown a  std::exception()  the last log instructions were missing
    //inside the log file.
    return 1 ;
  }
  return 1 ;
}

PDH_CPUcoreUsageGetter::PDH_CPUcoreUsageGetter()
  : 
  m_ar_pdh_cpu_core_usage_getter_per_core_atts( NULL)
  , m_lpwstrPercentProcessorTimeCounterName(NULL)
  , m_lpwstrProcessorPerfObjectName(NULL)
{
//#ifdef _DEBUG
//  std::string strExeFileNameWithoutDirs = GetStdString( GetExeFileNameWithoutDirs() ) ;
//  std::string stdstrFilename = strExeFileNameWithoutDirs +
//      ("PDH_CPUcoreUsageGetterDLL_log.txt") ;
//  g_logger.OpenFile2( stdstrFilename ) ;
//  DEBUGN("this Log file is open")
//#endif
  DEBUGN("PDH_CPUcoreUsageGetter::PDH_CPUcoreUsageGetter" )
#ifdef _MSC_VER
  GetPercentProcessorTimeName() ;
    //StartPerfCounting() ;
#endif //#ifndef _MSC_VER
}

PDH_CPUcoreUsageGetter::~PDH_CPUcoreUsageGetter()
{
  //PdhCloseQuery(hQuery);
  if( m_lpwstrPercentProcessorTimeCounterName )
    delete [] m_lpwstrPercentProcessorTimeCounterName ;
  if( m_lpwstrProcessorPerfObjectName )
    delete [] m_lpwstrProcessorPerfObjectName ;
  if( m_ar_pdh_cpu_core_usage_getter_per_core_atts )
  {
    for(WORD wCoreID = 0 ; wCoreID < m_wNumLogicalCPUcores ; ++ wCoreID )
      PdhCloseQuery( m_ar_pdh_cpu_core_usage_getter_per_core_atts[ wCoreID ].
        hQuery) ;
    delete [] m_ar_pdh_cpu_core_usage_getter_per_core_atts ;
  }
}

void PDH_CPUcoreUsageGetter::AssignDLLfunctionPointers()
{
#ifdef COMPILE_RUNTIME_DYN_LINKED
  std::string stdstrFuncName ;

  stdstrFuncName = "PdhAddCounterW" ;
  m_pfnPdhAddCounterW = (PdhAddCounterW_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhAddCounterW == NULL )
    throw //std::exception() ;
    ExceptionWithStdString(stdstrFuncName) ;

  if(atLeastWinVista() ){
    stdstrFuncName = "PdhAddEnglishCounterW" ;
    m_pfnPdhAddEnglishCounterW = (PdhAddEnglishCounterW_type)
      ::GetProcAddress(m_hinstancePDH_DLL, stdstrFuncName.c_str() );
    if( m_pfnPdhAddEnglishCounterW == NULL )
      throw ExceptionWithStdString(stdstrFuncName) ;
  }
  else
    m_pfnPdhAddEnglishCounterW = NULL;

  stdstrFuncName = "PdhCloseQuery" ;
  m_pfnPdhCloseQuery = (PdhCloseQuery_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhCloseQuery == NULL )
    throw //std::exception() ;
    ExceptionWithStdString(stdstrFuncName) ;

  stdstrFuncName = "PdhCollectQueryData" ;
  m_pfnPdhCollectQueryData = (PdhCollectQueryData_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhCollectQueryData == NULL )
    throw //std::exception() ;
  ExceptionWithStdString(stdstrFuncName) ;

  stdstrFuncName = "PdhEnumObjectsW" ;
  m_pfnPdhEnumObjectsW = (PdhEnumObjectsW_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhCollectQueryData == NULL )
    throw //std::exception() ;
  ExceptionWithStdString(stdstrFuncName) ;

  stdstrFuncName = "PdhGetFormattedCounterValue" ;
  m_pfnPdhGetFormattedCounterValue = (PdhGetFormattedCounterValue_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhGetFormattedCounterValue == NULL )
    throw //std::exception() ;
  ExceptionWithStdString(stdstrFuncName) ;

  stdstrFuncName = "PdhOpenQueryW" ;
  m_pfnPdhOpenQueryW = (PdhOpenQueryW_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhOpenQueryW == NULL )
    throw //std::exception() ;
  ExceptionWithStdString(stdstrFuncName) ;

  stdstrFuncName = "PdhLookupPerfNameByIndexW" ;
  m_pfnPdhLookupPerfNameByIndexW = (PdhLookupPerfNameByIndexW_type)
    ::GetProcAddress( m_hinstancePDH_DLL, stdstrFuncName.c_str() );
  if( m_pfnPdhLookupPerfNameByIndexW == NULL )
    throw //std::exception() ;
  ExceptionWithStdString(stdstrFuncName) ;

  DEBUGN("all DLL fct ptrs assigned")
#endif //#ifndef COMPILE_RUNTIME_DYN_LINKED
}

LPWSTR PDH_CPUcoreUsageGetter::GetPerfnameByIndex(WORD wIndex )
{
  DWORD dwNameBufferSize;
  LPWSTR lpwstrCounterName;
//  if(isWindowsXP() ){
    /** http://msdn.microsoft.com/en-us/library/aa372648%28VS.85%29.aspx:
     * "Windows XP:  You must specify a buffer and buffer size." */
    dwNameBufferSize = PDH_MAX_COUNTER_NAME + 1;
    lpwstrCounterName = new WCHAR [ dwNameBufferSize ] ;
//  }
  //else{
    /** https://docs.microsoft.com/en-us/windows/win32/api/pdh/nf-pdh-pdhlookupperfnamebyindexw
     * "You should call this function twice, the first time to get the required
     * buffer size (set szNameBuffer to NULL and pcchNameBufferSize to 0), and
     * the second time to get the data." */
//    dwNameBufferSize = 0;
//    lpwstrCounterName = NULL;    
//  }
  
//  WCHAR lpwstrCounterName [1] ;
  //  LPTSTR szNameBuffer ;
  //http://msdn.microsoft.com/en-us/library/aa372648(v=VS.85).aspx:
  //Performance counter names for PdhAddCounter(...) depend on the
  //machine language. the alternative PdhAddEnglishCounter(...) exists from
  //version 6, so it is not usable for winXP.
  //To make it independent, get the name from the index.
  PDH_STATUS pdh_status = PdhLookupPerfNameByIndexW(
    //"If NULL, the function uses the local computer."
    NULL ,//__in   LPCTSTR szMachineName,
    wIndex, //__in   DWORD dwNameIndex,
    //__out  LPTSTR szNameBuffer,
    //"Set to NULL if pcchNameBufferSize is zero."
//    NULL ,
    lpwstrCounterName ,
    //"If zero on input, the function returns PDH_MORE_DATA and sets this
    //parameter to the required buffer size."
    //"If the specified size on input is greater than zero but less than the
    //required size, you should not rely on the returned size to reallocate the
    //buffer."
    & dwNameBufferSize //__in   LPDWORD pcchNameBufferSize
    ) ;
  switch( pdh_status )
  {
    case ERROR_SUCCESS:
      DEBUGN("PdhLookupPerfNameByIndexW succeeded for index " << wIndex )
      break ;
    case PDH_MORE_DATA:
      /**http://msdn.microsoft.com/en-us/library/aa372648%28VS.85%29.aspx :
       * paragraph "Remarks" -> "Windows XP":
       * "If the buffer is too small, the function returns 
       * PDH_INSUFFICIENT_BUFFER instead of PDH_MORE_DATA" */
    case PDH_INSUFFICIENT_BUFFER:
    {
      //Release dynamically (on heap) created memory.
      delete [] lpwstrCounterName ;
      DEBUGN( "PdhLookupPerfNameByIndexW: namebuffer size:" << dwNameBufferSize )
      lpwstrCounterName = new WCHAR[ dwNameBufferSize] ;
      if( lpwstrCounterName )
      {
      //  DEBUGWN(L"percent processor time name:" <<
      //    m_lpwstrPercentProcessorTimeCounterName )
      //  DEBUGWN_WSPRINTF( L"percent processor time name:%ls" ,
      //    m_lpwstrPercentProcessorTimeCounterName )
        //"If the function succeeds, it returns ERROR_SUCCESS. "
        PDH_STATUS pdh_status =
          PdhLookupPerfNameByIndexW(
          //"If NULL, the function uses the local computer."
          NULL ,//__in   LPCTSTR szMachineName,
          //// "% Processor Time" in the English language
          wIndex , //__in   DWORD dwNameIndex,
          lpwstrCounterName ,// __out  LPTSTR szNameBuffer,
          //"If zero on input, the function returns PDH_MORE_DATA and sets this
          //parameter to the required buffer size."
          & dwNameBufferSize //__in   LPDWORD pcchNameBufferSize
          ) ;
        if( pdh_status == ERROR_SUCCESS )
        {
          DEBUGN("PdhLookupPerfNameByIndexW succeeded for index " << wIndex )
        }
        else
        {
          lpwstrCounterName = NULL ;
          DEBUGN("PdhLookupPerfNameByIndexW failed for index " << wIndex )
        }
      }
    }
    break ;
    default:
    {
      std::wstring wstr ;
      if ( GetPDHerrorCodeString( pdh_status , wstr ) )
        DEBUGWN_WSPRINTF(L"PdhLookupPerfNameByIndexW failed for index %u :%ls",
          wIndex ,
          wstr.c_str() )
    }
  }
  /** Happened in Win 7 64 bit that ERROR_SUCCESS from PdhLookupPerfNameByIndexW
   * but counter name was empty (there was no such name in registry path
   * HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib\009
   * ) */
  if( wcscmp(lpwstrCounterName, L"") == 0){
    delete [] lpwstrCounterName;
    std::wostringstream woss;
    woss << L"After calling \"PdhLookupPerfNameByIndexW\" with index " << wIndex
      << L": counter name is empty";
//    std::wstring wstr= GetStdWstring(woss.str().c_str() );
    throw CPUcoreUsageException(woss.str().c_str() );
  }
//  //Release dynamically (on heap) created memory.
//  delete [] lpwstrCounterName ;
  return lpwstrCounterName ;
}

void PDH_CPUcoreUsageGetter::GetPercentProcessorTimeName()
{
  DEBUGN(/*"PDH_CPUcoreUsageGetter::GetPercentProcessorTimeName"*/ "begin" )
  m_lpwstrPercentProcessorTimeCounterName = GetPerfnameByIndex(
    //http://msdn.microsoft.com/en-us/library/aa372648%28VS.85%29.aspx:
    //can be seen in registry path
    //"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib\009"
    //, name: "Counter"
    // "% Processor Time" in the English language
    6
    ) ;
  if( m_lpwstrPercentProcessorTimeCounterName )
  {
#ifdef _DEBUG
    std::wstring wstr(m_lpwstrPercentProcessorTimeCounterName) ;
//    DEBUGWN("successfully got percent processor time name:"
//        << m_lpwstrPercentProcessorTimeCounterName
//      << wstr )
    DEBUGWN_WSPRINTF(L"successfully got percent processor time name:%ls"
        , m_lpwstrPercentProcessorTimeCounterName )
    //DEBUGN("percent processor time name:" << m_lpwstrPercentProcessorTimeCounterName )
#endif
  }
  else
  {
    DEBUGN("GetPercentProcessorTimeName--GetPerfnameByIndex failed")
    throw std::exception() ;
  }
  //TODO: PdhEnumObjects() :
  //http://msdn.microsoft.com/en-us/library/aa372600%28VS.85%29.aspx
  //to get the localized Object name? :
  //  -in English Windows for Adding a counter : "Processor(0)"
  //  -in German Windows for Adding a counter : "Prozessor(0)"

  //see also http://support.microsoft.com/kb/287159
}

#ifndef PERF_DETAIL_NOVICE
//TODO check if this is right
//#define PERF_DETAIL_NOVICE 0
#endif

void PDH_CPUcoreUsageGetter::GetCounterObjects()
{
  //try to get the object name for "processor" in the system language
  //(e.g. "Prozessor" for German Windows version)
  DWORD dwpcchBufferLength = 0 ;
  //cites from:
  //http://msdn.microsoft.com/en-us/library/aa372600%28VS.85%29.aspx
  PDH_STATUS pdh_stat = PdhEnumObjectsW(
    //"If NULL, the function uses the computer specified in the szMachineName
    //parameter to enumerate the names."
    NULL , //__in     LPCTSTR szDataSource,
    //"If the szDataSource parameter is NULL, you can set szMachineName  to
    //NULL to specify the local computer. "
    NULL , //__in     LPCTSTR szMachineName,
    //"Set to NULL if the pcchBufferLength parameter is zero."
    NULL , //__out    LPTSTR mszObjectList,
    //"If zero on input, the function returns PDH_MORE_DATA and sets this
    //parameter to the required buffer size."
    & dwpcchBufferLength , //__inout  LPDWORD pcchBufferLength,
//    PERF_DETAIL_ADVANCED , //__in     DWORD dwDetailLevel,
    PERF_DETAIL_NOVICE ,
    FALSE //__in     BOOL bRefresh
  );
  DEBUGN("res of PdhEnumObjects:" << pdh_stat)
  if( //explicit cast to to ULONG avoid g++ compiler warning
      //"comparison between signed and unsigned integer expressions"
      (ULONG) pdh_stat == PDH_MORE_DATA )
  {
    DEBUGN("res of PdhEnumObjects: PDH_MORE_DATA: " << dwpcchBufferLength )
//  LPTSTR mszObjectList = new TCHAR[ dwpcchBufferLength ] ;
    LPWSTR mszObjectList = new WCHAR[ dwpcchBufferLength ] ;
    if( mszObjectList )
    {
      DEBUGN("succ allocated the obj name array")
      pdh_stat = PdhEnumObjectsW(
        //"If NULL, the function uses the computer specified in the szMachineName
        //parameter to enumerate the names."
        NULL , //__in     LPCTSTR szDataSource,
        //"If the szDataSource parameter is NULL, you can set szMachineName  to
        //NULL to specify the local computer. "
        NULL , //__in     LPCTSTR szMachineName,
        //"Set to NULL if the pcchBufferLength parameter is zero."
        mszObjectList , //__out    LPTSTR mszObjectList,
        //"If zero on input, the function returns PDH_MORE_DATA and sets this
        //parameter to the required buffer size."
        & dwpcchBufferLength , //__inout  LPDWORD pcchBufferLength,
//        PERF_DETAIL_ADVANCED , //__in     DWORD dwDetailLevel,
        PERF_DETAIL_NOVICE , //__in     DWORD dwDetailLevel,
        FALSE //__in     BOOL bRefresh
      );
      DEBUGN("res of PdhEnumObjects:" << pdh_stat )
      if( pdh_stat == ERROR_SUCCESS )
      {
#ifdef _DEBUG
        OutputMultiWStringValue(mszObjectList) ;
#endif
//        if( ! * mszObjectList )
//        {
//          DEBUGWN_WSPRINTF( L"%ls", *mszObjectList )
//        }
      }
    }
  }
}

void OutputMultiWStringValue(LPWSTR mszObjectList)
{
#ifdef _DEBUG
  DWORD dwIndex = 0 ;
#endif
  //http://msdn.microsoft.com/en-us/library/aa372600%28VS.85%29.aspx:
  do
  {
    //Prints until first "\0"
    DEBUGWN_WSPRINTF( L"%ls, index:%u", mszObjectList , ++ dwIndex )
    //"Each object name in this list is terminated by a null character.
    //The list is terminated with two null-terminator characters."
    while( * mszObjectList )
    {
      //Print out 1 char
      //DEBUG( *mszObjectList )
      //DEBUGWN_WSPRINTF( L"%lc", *mszObjectList )
  //            DEBUGWN_WSPRINTF( L"%ls", *mszObjectList )
      ++ mszObjectList ;
    }
    DEBUG("\n")
  //If second NULL char (end of list) here it leaves the loop.
  }while( * (++ mszObjectList) ) ;
}

//inline
float PDH_CPUcoreUsageGetter::
  GetPercentalUsageForCore(
  BYTE byCoreID
  )
{
//  float fRet = -1.0 ;
//  m_fReturnValue = -1.0 ;
//  PDH_STATUS pdh_status ;
  DEBUGN(//"PDH_CPUcoreUsageGetter::GetPercentalUsageForCore"
    " for core " << (WORD) byCoreID )
//  printf("Starting the process...\n");

  //pdh_status = PdhCollectQueryData(
  //  //"Handle of the query for which you want to collect data. The
  //  //PdhOpenQuery function returns this handle."
  //  hQuery );
  //if( pdh_status == ERROR_SUCCESS )
  {
    //DEBUGN("PdhCollectQueryData succeeded")
     // Read the next record
    //pdh_status
    m_pdh_status = PdhCollectQueryData(
      //hQuery
      m_ar_pdh_cpu_core_usage_getter_per_core_atts[byCoreID].hQuery
      );

    if ( //ERROR_SUCCESS == pdh_status )
        m_pdh_status == ERROR_SUCCESS)
    {
//      PDH_FMT_COUNTERVALUE FmtValue ;
      DEBUGN("PdhCollectQueryData succeeded")
//      pdh_status =
      m_pdh_status =
        //http://msdn.microsoft.com/en-us/library/aa372637%28v=VS.85%29.aspx:
        //"If the function succeeds, it returns ERROR_SUCCESS. "
        PdhGetFormattedCounterValue(
        //"The PdhAddCounter function returns this handle."
        //hCounter,
        m_ar_pdh_cpu_core_usage_getter_per_core_atts[byCoreID].hCounter ,
        PDH_FMT_DOUBLE,
        //"Receives the counter type. For a list of counter types, see
        //the Counter Types section of the Windows Server 2003 Deployment
        //Kit. This parameter is optional."
        NULL,
//        & FmtValue
        & m_pdh_fmt_countervalue
        );
      if( //pdh_status
          m_pdh_status == ERROR_SUCCESS )
      {
        DEBUGN("PdhGetFormattedCounterValue succeeded")
        DEBUGN("PDH_CPUcoreUsageGetter::GetPercentalUsageForCore for core usage:"
          << std::ios::hex << m_pdh_fmt_countervalue.doubleValue )
//        fRet = FmtValue.doubleValue ;
        m_fReturnValue = m_pdh_fmt_countervalue.doubleValue ;
        //The caller expects value in range [0...1]
        return m_fReturnValue / 100.0 ;
      }
      else
      {
#ifdef _DEBUG
        std::wstring wstr ;
        if( GetPDHerrorCodeString(m_pdh_status, wstr) )
          DEBUGN("PdhGetFormattedCounterValue failed: " << (DWORD) m_pdh_status
            << wstr )
#endif
      }
    }
    else
    {
      DEBUGN("PdhCollectQueryData failed")
      std::wstring wstr ;
      if( GetPDHerrorCodeString(//pdh_status
        m_pdh_status, wstr) )
      {
        DEBUGN("GetPDHerrorCodeString succeeded")
        //MinGW has no std::wstringstream -> use wprintf(..)
//        DEBUGWN( L"PdhCollectQueryData failed: " << (DWORD) pdh_status
//          << wstr )
        DEBUGWN_WSPRINTF( L"PdhCollectQueryData failed:%u %ls"
          , (DWORD) m_pdh_status
          , wstr.c_str()
          )
      }
      else
        DEBUGN("GetPDHerrorCodeString failed")
    }
  }
//  printf("The cpu usage is : %f%%\n", FmtValue.doubleValue);
//  //The caller expects value in range [0...1]
////  return fRet / 100.0 ;
//  return m_fReturnValue / 100.0 ;
  return -1.0 ;
}
#ifdef COMPILE_RUNTIME_DYN_LINKED
  PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhAddCounterW(
      __in  PDH_HQUERY     hQuery,
      __in  LPCWSTR        szFullCounterPath,
      __in  DWORD_PTR      dwUserData,
      __out PDH_HCOUNTER * phCounter
  )
  {
    return (*m_pfnPdhAddCounterW) (
        hQuery ,
        szFullCounterPath ,
        dwUserData ,
        phCounter ) ;
  }
  PDH_FUNCTION PDH_CPUcoreUsageGetter::PdhAddEnglishCounterW(
    __in  PDH_HQUERY hQuery,
    __in  LPCWSTR szFullCounterPath,
    __in  DWORD_PTR dwUserData,
    __out PDH_HCOUNTER * phCounter
    )
  {
    return (*m_pfnPdhAddEnglishCounterW)(
      hQuery,
      szFullCounterPath,
      dwUserData,
      phCounter);
  }
  PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhCloseQuery(
      __inout PDH_HQUERY hQuery
  )
  {
    return (*m_pfnPdhCloseQuery) ( hQuery ) ;
  }
  inline PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhCollectQueryData(
      __inout PDH_HQUERY hQuery
  )
  {
    return (*m_pfnPdhCollectQueryData) ( hQuery ) ;
  }
  PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhEnumObjectsW(
    __in_opt LPCWSTR szDataSource,
    __in_opt LPCWSTR szMachineName,
    __out_ecount_opt(* pcchBufferSize) PZZWSTR mszObjectList,
    __inout  LPDWORD pcchBufferSize,
    __in     DWORD   dwDetailLevel,
    __in     BOOL    bRefresh
    )
  {
    return (*m_pfnPdhEnumObjectsW) (
      szDataSource,
      szMachineName,
      mszObjectList,
      pcchBufferSize,
      dwDetailLevel,
      bRefresh
      ) ;
  }
  inline PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhGetFormattedCounterValue(
      __in      PDH_HCOUNTER          hCounter,
      __in      DWORD                 dwFormat,
      __out_opt LPDWORD               lpdwType,
      __out     PPDH_FMT_COUNTERVALUE pValue
  )
  {
    return (*m_pfnPdhGetFormattedCounterValue) (
        hCounter ,
        dwFormat ,
        lpdwType ,
        pValue ) ;
  }
  PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhLookupPerfNameByIndexW(
    __in_opt LPCWSTR szMachineName,
    __in     DWORD   dwNameIndex,
    __out_ecount_opt(* pcchNameBufferSize) LPWSTR  szNameBuffer,
    __inout  LPDWORD pcchNameBufferSize
    )
  {
    return (*m_pfnPdhLookupPerfNameByIndexW) (
      szMachineName ,
      dwNameIndex ,
      szNameBuffer ,
      pcchNameBufferSize
     ) ;
  }
  PDH_FUNCTION
  PDH_CPUcoreUsageGetter::PdhOpenQueryW(
      __in_opt LPCWSTR      szDataSource,
      __in     DWORD_PTR    dwUserData,
      __out    PDH_HQUERY * phQuery
  )
  {
    return (*m_pfnPdhOpenQueryW) (
      szDataSource ,
      dwUserData ,
      phQuery
      ) ;
  }
#endif //#ifdef COMPILE_RUNTIME_DYN_LINKED

void PDH_CPUcoreUsageGetter::SetNumberOfCPUcores( WORD wNumLogicalCPUcores )
{
  DEBUGN(//"PDH_CPUcoreUsageGetter::SetNumberOfCPUcores(" <<
    wNumLogicalCPUcores << ")" )
  m_wNumLogicalCPUcores = wNumLogicalCPUcores ;
  m_ar_pdh_cpu_core_usage_getter_per_core_atts = new 
    PDH_CPUcoreUsageGetterPerCoreAtts[ wNumLogicalCPUcores ] ;
  StartPerfCounting() ;
}

void PDH_CPUcoreUsageGetter::InitPDH_Names()
{
  GetPercentProcessorTimeName() ;
  //GetCounterObjects() ;
  //LPWSTR lpwstr
  m_lpwstrProcessorPerfObjectName = GetPerfnameByIndex(
    //index for "processor" performance counter object
    238) ;
  if( //lpwstr
    m_lpwstrProcessorPerfObjectName )
  {
    DEBUGWN_WSPRINTF( L"processor perf ctr obj in local lang:%ls" , //lpwstr
        m_lpwstrProcessorPerfObjectName )
  }
}

inline void constructPerfCnterName(
  const fastestUnsignedDataType CPUcoreID,
  LPWSTR lpwstrProcessorPerfObjectName,
  LPWSTR lpwstrPercentProcessorTimeCounterName,
  std::wstring & stdwstr)
{
  LPWSTR lpwstrCPUcoreNumber;
  wchar_t ar_wch[20];
  lpwstrCPUcoreNumber = _itow(CPUcoreID, ar_wch, 10);
//    DEBUGWN( L"core number as string:" << m_lpwstrCPUcoreNumber )
  //TODO German version starts with "Prozessor"?
  if(lpwstrProcessorPerfObjectName )
    stdwstr = L"\\" + std::wstring(lpwstrProcessorPerfObjectName) + L"("
      /** In performance monitor ("perfmon.exe") for Windows 7 and core 3 it is:
       *  "Processor Information(0,3)\% Processor Time", previously it was
       *  "Processor(3)\% Processor Time" */
      L"0,";
//    else
//      stdwstr = std::wstring( L"\\Processor(" ) ;
  stdwstr += lpwstrCPUcoreNumber + std::wstring(L")\\") ;
  stdwstr += lpwstrPercentProcessorTimeCounterName;
}

void PDH_CPUcoreUsageGetter::StartPerfCounting( )
{
  bool useLocalLanguageNames = false;
//  if(! atLeastWinVista() )
//    useLocalNames = false;
  if(useLocalLanguageNames)
    InitPDH_Names();

  PDH_STATUS pdh_status ;
  //std::wstring stdwstr(L"\\Processor(0)\\") ;
//  std::wstring stdwstr( //L"\\Processor(_Total)\\"
//    //TODO German version start with "Prozessor"?
////    L"\\Processor(\\") ;
//    L"\\Processor(\\") ;
//  DEBUGWN("percent processor time name:" <<
//      m_lpwstrPercentProcessorTimeCounterName )
  for(fastestUnsignedDataType CPUcoreID = 0 ; CPUcoreID < m_wNumLogicalCPUcores;
    ++ CPUcoreID)
  {
    std::wstring stdwstrPerfCntrName;
    DEBUGWN_WSPRINTF(L"full query:%ls" , stdwstr.c_str() )
    //http://msdn.microsoft.com/en-us/library/aa372652%28v=VS.85%29.aspx:
    //"If the function succeeds, it returns ERROR_SUCCESS."
    pdh_status = PdhOpenQueryW(
      //"If NULL, performance data is collected from a real-time data source. "
      NULL,
      //"User-defined value to associate with this query. To retrieve the user 
      //data later, call PdhGetCounterInfo and access the dwQueryUserData 
      //member of PDH_COUNTER_INFO."
      //0,
      CPUcoreID,
      //"Handle to the query."
      //& hQuery
      & m_ar_pdh_cpu_core_usage_getter_per_core_atts[CPUcoreID].hQuery
      );
    if( pdh_status == ERROR_SUCCESS )
      DEBUGN("PdhOpenQuery succeeded")
    else
      DEBUGN("PdhOpenQuery failed")

    if(/*! atLeastWinVista()*/ //false 
       useLocalLanguageNames)
    {
      constructPerfCnterName(
        CPUcoreID,
        m_lpwstrProcessorPerfObjectName,
        m_lpwstrPercentProcessorTimeCounterName,
        stdwstrPerfCntrName);
      delete [] m_lpwstrPercentProcessorTimeCounterName;
      m_lpwstrPercentProcessorTimeCounterName = NULL;
      pdh_status = PdhAddCounterW( 
        m_ar_pdh_cpu_core_usage_getter_per_core_atts[CPUcoreID].hQuery ,
        //http://technet.microsoft.com/en-us/library/cc784617%28WS.10%29.aspx:
        //"An instance called _Total instance is available on most objects and
        //represents the sum of the values for all instances of the object for a
        //specific counter."
        //L"\\Processor(_Total)\\% Processor Time" ,
        //L"\\Processor(0)\\% Processor Time" ,
        stdwstrPerfCntrName.c_str() ,
        /** "User-defined value. This value becomes part of the counter
         * information. To retrieve this value later, call the PdhGetCounterInfo
         * function and access the dwUserData member of the PDH_COUNTER_INFO
         * structure." */
        CPUcoreID,//0,
        & m_ar_pdh_cpu_core_usage_getter_per_core_atts[CPUcoreID].hCounter
        );
      if(pdh_status != ERROR_SUCCESS){
        std::wstring wstrPDHerror;
        GetPDHerrorCodeString(pdh_status, wstrPDHerror);
        std::wstring msg = L"error calling PdhAddCounterW with parameter "
          L"\"" + stdwstrPerfCntrName + L"\":" + wstrPDHerror;
        throw CPUcoreUsageException(msg.c_str() );
      }
    }
    else{
      constructPerfCnterName(
        CPUcoreID,
        /** In performance monitor ("perfmon.exe") for Windows 7 it is:
         *  "Processor Information(0,3)\% Processor Time" */
        CAST_TO_WCHAR_POINTER /*L"Processor"*/ L"Processor Information",
        CAST_TO_WCHAR_POINTER L"% Processor Time",
        stdwstrPerfCntrName);///0x3e508 L"\\\\Processor(0)\\\\% Processor Time"
      ///For testing (1st CPU core):
      //stdwstrPerfCntrName = L"\\Processor Information(0,0)\\% Processor Time";
      pdh_status =
        ///"Minimum supported client Windows Vista"
        PdhAddEnglishCounterW(
        m_ar_pdh_cpu_core_usage_getter_per_core_atts[CPUcoreID].hQuery,
        stdwstrPerfCntrName.c_str(),
        CPUcoreID,
        & m_ar_pdh_cpu_core_usage_getter_per_core_atts[CPUcoreID].hCounter);
      if(pdh_status != ERROR_SUCCESS){
        std::wstring wstrPDHerror;
        GetPDHerrorCodeString(pdh_status, wstrPDHerror);
        std::wstring msg = L"error calling PdhAddEglishCounterW with parameter "
          L"\"" + stdwstrPerfCntrName + L"\":" + wstrPDHerror;
        throw CPUcoreUsageException(msg.c_str() );
      }
    }
    if(pdh_status == ERROR_SUCCESS )
    {
      DEBUGN("PdhAdd(English)CounterW succeeded")
    }
  }
}
