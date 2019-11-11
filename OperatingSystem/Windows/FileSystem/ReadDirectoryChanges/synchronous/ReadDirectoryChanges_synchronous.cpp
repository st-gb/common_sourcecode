/* 
 * File:   ReadDirectoryChanges_synchronous.cpp
 * Author: Stefan
 * 
 * Created on 11. Dezember 2009, 13:10
 */

#include <string>
#include <Windows.h> //for CreateFile(...)
#include <iostream>

//::GetErrorMessageFromErrorCodeA(DWORD)
#include <Controller/GetErrorMessageFromLastErrorCode.hpp>
#include "ReadDirectoryChanges_synchronous.hpp"
#include "../ProcessReadDirectoryChangesRecords.hpp"

DWORD WINAPI WatchSubTreeThreadProc(LPVOID lpParameter)
{
//  std::string & tstrRootPath = * ( (std::string *) lpParameter ) ;
  struct S_FSwatch * ps_fswatch = ( struct S_FSwatch * ) lpParameter ;
  if( ps_fswatch )
  {
    //http://msdn.microsoft.com/en-us/library/aa363858%28VS.85%29.aspx:
    //If the function succeeds, the return value is an open handle to the
    //specified file, device, named pipe, or mail slot.
    //If the function fails, the return value is INVALID_HANDLE_VALUE
    HANDLE handleDirectory ;
    LOGN( "WatchSubTreeThreadProc" )
    handleDirectory = Windows::ReadDirectoryChangesW::GetHandleToDirectory(
      //ps_fswatch
      ps_fswatch->stdwstrRootPath) ;
    LOGN( "CreateFile result: " << handleDirectory )
    //http://msdn.microsoft.com/en-us/library/aa363858%28VS.85%29.aspx:
    //"If the function fails, the return value is INVALID_HANDLE_VALUE.
    //To get extended error information, call GetLastError."
    if( handleDirectory == INVALID_HANDLE_VALUE )
    {
      DWORD dwLastError = ::GetLastError() ;
      LOGN( LOG_CHAR_TYPE("creating dir handle failed:") <<
        ::GetErrorMessageFromErrorCodeA(
        //::GetErrorMessageFromErrorCodeW(
        dwLastError) )
//      throw FileSystemEventException(  ) ;
      return dwLastError ;
    }
    else
    {
      DWORD dwCurrentOffset = 0 ;
      DWORD dwBufferLength = READ_DIR_CHANGES_BUFFER_SIZE ;
      DWORD dwBytesReturned ;
      DWORD dwNotifyFilter =
        FILE_NOTIFY_CHANGE_FILE_NAME |
        FILE_NOTIFY_CHANGE_FILE_NAME |
        FILE_NOTIFY_CHANGE_ATTRIBUTES |
        FILE_NOTIFY_CHANGE_SIZE |
        FILE_NOTIFY_CHANGE_LAST_WRITE ;
  //    LPVOID lpvoid ;
      FILE_NOTIFY_INFORMATION * p_file_notify_information
       //Init with NULL to avoid g++'s "might be used uninitialized" warning.
        = NULL ;
      BYTE arby[READ_DIR_CHANGES_BUFFER_SIZE] ;
      BOOL boolReadDirectoryChangesW_succeeded ;
      LOGN( "creating dir handle succeeded" )
      //ReadDirectoryChangesW fails with ERROR_INVALID_PARAMETER when the
      //buffer length is greater than 64 KB and the application is monitoring
      //a directory over the network. This is due to a packet size limitation
      //with the underlying file sharing protocols.
      //ReadDirectoryChangesW fails with ERROR_NOACCESS when the buffer is
      //not aligned on a DWORD boundary.
      //If the function succeeds, the return value is nonzero.

  //    FileOrDirWatchAttributes file_or_dir_watch_info ;
      FileOrDirWatchInfo file_or_dir_watch_info ;
      while( ps_fswatch->m_v_bWatch )
      {
        LOGN( "WatchSubTreeThreadProc--waiting for a file system change" );
        //If used synchronously: the function returns after an event occured?
        //http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx:
        //"If the function succeeds, the return value is nonzero. For synchronous
        //calls, this means that the operation succeeded. For asynchronous
        //calls, this indicates that the operation was successfully queued."
        boolReadDirectoryChangesW_succeeded =
          ::ReadDirectoryChangesW(
          //http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx:
          //"This directory must be opened with the FILE_LIST_DIRECTORY access right."
          handleDirectory , //__in         HANDLE hDirectory,
          //lpvoid
          arby , //__out        LPVOID lpBuffer,
          dwBufferLength , //__in         DWORD nBufferLength,
          TRUE ,//__in         BOOL bWatchSubtree,
          dwNotifyFilter , //__in         DWORD dwNotifyFilter,
          & dwBytesReturned , //__out_opt    LPDWORD lpBytesReturned,
          NULL ,//__inout_opt  LPOVERLAPPED lpOverlapped,
          NULL //__in_opt     LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
        );
        if( boolReadDirectoryChangesW_succeeded )
        {
          LOGN( "ReadDirectoryChangesW succeeded." );
          if( ps_fswatch->m_v_bWatch )
          ProcessReadDirectoryChangesRecords(
            dwCurrentOffset,
            p_file_notify_information,
            arby,
            file_or_dir_watch_info,
            ps_fswatch);
        }
        else
        {
          LOGN( "ReadDirectoryChangesW failed." );
//          throw FileSystemEventException( ::GetLastError() ) ;
          return ::GetLastError() ;
        }
      }
      LOGN("WatchSubTreeThreadProc--ps_fswatch->m_v_bWatch is false")
      ::CloseHandle(handleDirectory);
      //Dyn. created before ::CreateThread(...);
      delete ps_fswatch;
    }
  }
  return 0 ;
}

using namespace Windows ;

ReadDirectoryChanges_synchronous::ReadDirectoryChanges_synchronous()
{
}

ReadDirectoryChanges_synchronous::ReadDirectoryChanges_synchronous(
  const ReadDirectoryChanges_synchronous& orig)
{
}

ReadDirectoryChanges_synchronous::~ReadDirectoryChanges_synchronous() {
}

//void
BYTE ReadDirectoryChanges_synchronous::EndWatchSubTree(
  const std::wstring & cr_std_wstrRootPath
  )
{
  std::map<std::wstring, struct S_FSwatch>::iterator iter =
    m_std_map_std_wstringFSWrootPath2s_fs_watch.find(
      cr_std_wstrRootPath );
  if( iter != m_std_map_std_wstringFSWrootPath2s_fs_watch.end() )
  {
      iter->second.m_v_bWatch = false;
//      if( m_std_map_std_wstringFSWrootPath2s_fs_watch.erase(iter) )
      m_std_map_std_wstringFSWrootPath2s_fs_watch.erase(iter);
      return 0;
  }
  return 1;
}

//Return value: success or failure.
//BYTE
DWORD ReadDirectoryChanges_synchronous::WatchSubTree(
//  const std::tstring & tstrRootPath ,
  const std::wstring & cr_stdwstrRootPath ,
//  void (* callback )( WCHAR * FileName, DWORD FileNameLength, DWORD Action )
  watch_handler callback
  )
{
  DWORD dwThreadId ;
  //Save the string into a structure so that accessing it is valid with the
  //new created thread (if we only pass a pointer to the string parameter
  //of THIS method the pointer may be invalid after leaving this funtion).
//  std::pair <std::set<std::tstring>::iterator, bool> stdpair =
//    m_stdset_stdtstrWatchedDir.insert( tstrRootPath ) ;
  std::pair <std::set<std::wstring>::iterator, bool> stdpair =
    m_stdset_stdtstrWatchedDir.insert( cr_stdwstrRootPath ) ;

  //Create on heap, else destroyed at the end of this block.
  struct S_FSwatch * p_s_fs_watch = new struct S_FSwatch(callback,
      cr_stdwstrRootPath, true );
  if( p_s_fs_watch )
  {
    m_std_map_std_wstringFSWrootPath2s_fs_watch.insert(
        std::make_pair(cr_stdwstrRootPath, * p_s_fs_watch) );
//    m_s_fs_watch.pf_Callback = callback ;
//  //  m_s_fs_watch.tstrRootPath = tstrRootPath ;
//    m_s_fs_watch.stdwstrRootPath = cr_stdwstrRootPath ;
//    m_s_fs_watch.m_v_bWatch = true ;
  //  std::cout << "before CreateThread\n" ;
    HANDLE handleThread = ::CreateThread(
      NULL,                   // NULL = default security attributes
      0,                      // 0 = use default stack size
      WatchSubTreeThreadProc ,      // thread function name
      //lpParameter
  //    (void *) //cast "const void *" to "void *"
  //    ( //address of std::tstring
  //      &
  //      (* //std::tstring
  //      //iterator
  //      stdpair.first)
  //    )
      // argument to thread function
//      & m_s_fs_watch ,
      p_s_fs_watch,
      0,                      // use default creation flags
      & dwThreadId
      );   // returns the thread identifier
    ::CloseHandle(handleThread) ;
  }
  return //true ;
    0 ;
//  std::cout << "after CreateThread\n" ;
}

//BYTE ReadDirectoryChanges_synchronous::EndWatchSubTree(
//  const std::string & strRootPath  )
//{
//
//}
