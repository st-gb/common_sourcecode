/*
 * ReadDirectoryChanges_asynchronous.cpp
 *
 *  Created on: Nov 15, 2010
 *      Author: Stefan
 */

#include <windef.h> //CALLBACK
#include <windows.h> //VOID, LPOVERLAPPED

#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
#include "../ProcessReadDirectoryChangesRecords.hpp"
#include "ReadDirectoryChanges_asynchronous.hpp"

OVERLAPPED g_overlapped ;
BYTE g_arby[READ_DIR_CHANGES_BUFFER_SIZE] ;
HANDLE g_handleDirectory ;
struct S_FSwatch g_fswatch ;
watch_handler g_watch_handler ;

//From http://msdn.microsoft.com/en-us/library/aa364052%28v=VS.85%29.aspx:
VOID CALLBACK FileIOCompletionRoutine(
  //__in
  DWORD dwErrorCode,
  //__in
  DWORD dwNumberOfBytesTransfered,
  //__in
  LPOVERLAPPED lpOverlapped
  )
{
  DWORD dwCurrentOffset = 0 ;
  FileOrDirWatchInfo file_or_dir_watch_info ;
  FILE_NOTIFY_INFORMATION * p_file_notify_information
    //Init with NULL to avoid g++'s "might be used uninitialized" warning.
    = NULL ;
//  BYTE arby[READ_DIR_CHANGES_BUFFER_SIZE] ;
//  lpOverlapped->
  LOGN("FileIOCompletionRoutine:" << dwNumberOfBytesTransfered << "bytes")
  g_fswatch.pf_Callback = g_watch_handler ;
  ULONGLONG ullAddress ;
  ReadDirectoryChangesWparameters * p_readdirectorychangeswparameters ;
  ullAddress = lpOverlapped->OffsetHigh ;
  ullAddress <<= 32 ;
  ullAddress |= lpOverlapped->Offset ;
  p_readdirectorychangeswparameters = (ReadDirectoryChangesWparameters *)
    ullAddress ;
  ProcessReadDirectoryChangesRecords(
    dwCurrentOffset,
    p_file_notify_information,
//    g_arby,
    p_readdirectorychangeswparameters->arbyDataBuffer ,
    file_or_dir_watch_info,
    & g_fswatch
    ) ;
}

DWORD StartWatch(
  ReadDirectoryChangesWparameters & r_readdirectorychangeswparameters
  )
{
  DWORD dwBytesReturned ;
  DWORD dwReturnValue ;
  DWORD dwNotifyFilter =
    FILE_NOTIFY_CHANGE_FILE_NAME |
    FILE_NOTIFY_CHANGE_FILE_NAME |
    FILE_NOTIFY_CHANGE_ATTRIBUTES |
    FILE_NOTIFY_CHANGE_SIZE |
    FILE_NOTIFY_CHANGE_LAST_WRITE ;
  //g_handleDirectory
  r_readdirectorychangeswparameters.handleDirectory = Windows::
    ReadDirectoryChangesW::GetHandleToDirectory(
    //ps_fswatch
    r_readdirectorychangeswparameters.stdwstrRootPath,
    //bAsynchronous
    true) ;
  //Store the address of the struct.
  r_readdirectorychangeswparameters.overlapped.OffsetHigh =
    ( (ULONGLONG) ( & r_readdirectorychangeswparameters ) ) >> 32 ;
  r_readdirectorychangeswparameters.overlapped.Offset =
    (DWORD) & r_readdirectorychangeswparameters ;
  g_overlapped.hEvent = ::CreateEvent(
    NULL,    // default security attribute
    TRUE,    // manual reset event
//      TRUE, // initial state = signaled
    FALSE, // FALSE=initial state = non-signaled
    NULL // NULL=unnamed event object
    );
  r_readdirectorychangeswparameters.overlapped.hEvent = ::CreateEvent(
    NULL,    // default security attribute
    TRUE,    // manual reset event
    //Should be non-signaled in order to wait at "WaitForSingleObject(...)"
//    TRUE, // initial state = signaled
      FALSE, // FALSE=initial state = non-signaled
    NULL // NULL=unnamed event object
    );
  LOGN("StartWatch(...)--before ReadDirectoryChangesW(...)")
  //http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx:
  //"If the function succeeds, the return value is nonzero. For synchronous
  //calls, this means that the operation succeeded. For asynchronous
  //calls, this indicates that the operation was successfully queued."
  BOOL boolReadDirectoryChangesW_succeeded =
    ::ReadDirectoryChangesW(
    //http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx:
    //"This directory must be opened with the FILE_LIST_DIRECTORY access right."
    r_readdirectorychangeswparameters.handleDirectory,//__in HANDLE hDirectory
    //lpvoid
    r_readdirectorychangeswparameters.arbyDataBuffer, //__out LPVOID lpBuffer
    READ_DIR_CHANGES_BUFFER_SIZE , //__in         DWORD nBufferLength,
    TRUE ,//__in         BOOL bWatchSubtree,
    dwNotifyFilter , //__in         DWORD dwNotifyFilter,
    //"For asynchronous calls, this parameter is undefined."
    & dwBytesReturned , //__out_opt    LPDWORD lpBytesReturned,
    //__inout_opt  LPOVERLAPPED lpOverlapped,
//    & g_overlapped ,
    & r_readdirectorychangeswparameters.overlapped ,
//    & r_readdirectorychangeswparameters.overlapped ,
    //__in_opt     LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    FileIOCompletionRoutine
  );
  if( boolReadDirectoryChangesW_succeeded )
  {
    LOGN("ReadDirectoryChangesW succeeded.")
    return ERROR_SUCCESS ;
  }
  else
  {
    LOGN("ReadDirectoryChangesW failed.")
    //"If the function fails, the return value is zero. To get extended error
    //information, call GetLastError."
    dwReturnValue = ::GetLastError() ;
  }
  return dwReturnValue ;
}

DWORD WINAPI WatchSubTree_asynchronousThreadProc(LPVOID lpParameter)
{
  LOGN("WatchSubTree_asynchronousThreadProc")
  ReadDirectoryChangesWparameters * p_readdirectorychangeswparameters =
    ( ReadDirectoryChangesWparameters * ) lpParameter ;
  if( p_readdirectorychangeswparameters )
  {
      //  From http://msdn.microsoft.com/en-us/library/aa365601%28v=VS.85%29.aspx:
    HANDLE handleEvent ;
    LOGN("WatchSubTree_asynchronousThreadProc"
      "--address of p_readdirectorychangeswparameters:" <<
      p_readdirectorychangeswparameters
      << "address of p_readdirectorychangeswparameters->overlapped:"
      << & p_readdirectorychangeswparameters->overlapped)
//    handleEvent = ::CreateEvent(
//    p_readdirectorychangeswparameters->overlapped.hEvent = handleEvent ;
    handleEvent = p_readdirectorychangeswparameters->overlapped.hEvent ;
    LOGN("WatchSubTree_asynchronousThreadProc--event:" << handleEvent)
//    StartWatch( * p_readdirectorychangeswparameters) ;
    do
    {
      LOGN("WatchSubTree_asynchronousThreadProc--before WaitForSingleObjectEx")
      // Wait for a client to connect, or for a read or write
      // operation to be completed, which causes a completion
      // routine to be queued for execution.
      DWORD dwWait = ::WaitForSingleObjectEx(
    //      hConnectEvent,  // event object to wait for
//        handleEvent ,
//        g_overlapped.hEvent ,
        p_readdirectorychangeswparameters->overlapped.hEvent ,
//        p_readdirectorychangeswparameters->m_handleEventStopWatch ,
        INFINITE,       // waits indefinitely
        TRUE);          // alertable wait enabled
      LOGN("WatchSubTree_asynchronousThreadProc--after WaitForSingleObjectEx: "
          "ret val:" << dwWait )
      break  ;
//      ::ResetEvent(//handleEvent
//        p_readdirectorychangeswparameters->overlapped.hEvent) ;
    }
    while(p_readdirectorychangeswparameters->bContinue ) ;
    LOGN("WatchSubTree_asynchronousThreadProc--after loop")
    ::CloseHandle( p_readdirectorychangeswparameters->overlapped.hEvent) ;
    ::CloseHandle( p_readdirectorychangeswparameters->m_handleEventStopWatch) ;
    delete p_readdirectorychangeswparameters ;
  }
  LOGN("WatchSubTree_asynchronousThreadProc--end")
  return 0 ;
}

//If the file system watch should be cancellable it must be used asynchronously
//: it can not be interrupted if only 1 thread and it blocks at a call to
// "ReadDirectoryChangesW(...)"

//see http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx
//For asynchronous completion, you can receive notification in one of three ways:
//* Using the GetOverlappedResult function. To receive notification through GetOverlappedResult, do not specify a completion routine in the lpCompletionRoutine parameter. Be sure to set the hEvent member of the OVERLAPPED structure to a unique event.
//* Using the GetQueuedCompletionStatus function. To receive notification through GetQueuedCompletionStatus, do not specify a completion routine in lpCompletionRoutine. Associate the directory handle hDirectory with a completion port by calling the CreateIoCompletionPort function.
//* Using a completion routine. To receive notification through a completion routine, do not associate the directory with a completion port. Specify a completion routine in lpCompletionRoutine. This routine is called whenever the operation has been completed or canceled while the thread is in an alertable wait state. The hEvent member of the OVERLAPPED structure is not used by the system, so you can use it yourself.

//Return value: success or failure.
//BYTE
DWORD Windows::ReadDirectoryChanges_asynchronous::WatchSubTree(
//  const std::tstring & tstrRootPath ,
  const std::wstring & cr_stdwstrRootPath ,
//  void (* callback )( WCHAR * FileName, DWORD FileNameLength, DWORD Action )
  watch_handler callback
  )
{
  g_watch_handler = callback ;
//  //Save the string into a structure so that accessing it is valid with the
//  //new created thread (if we only pass a pointer to the string parameter
//  //of THIS method the pointer may be invalid after leaving this funtion).
////  std::pair <std::set<std::tstring>::iterator, bool> stdpair =
////    m_stdset_stdtstrWatchedDir.insert( tstrRootPath ) ;
//  std::pair <std::set<std::wstring>::iterator, bool> stdpair =
//    m_stdset_stdtstrWatchedDir.insert( cr_stdwstrRootPath ) ;
//  m_s_fs_watch.pf_Callback = callback ;
////  m_s_fs_watch.tstrRootPath = tstrRootPath ;
//  m_s_fs_watch.stdwstrRootPath = cr_stdwstrRootPath ;
//  m_s_fs_watch.m_v_bWatch = true ;

  //_Must_ create on heap: else it gets invalid after leaving _this_ block.
  ReadDirectoryChangesWparameters * p_readdirectorychangeswparameters =
    new ReadDirectoryChangesWparameters ;
  if( p_readdirectorychangeswparameters)
  {
    DWORD dwThreadId ;
    LOGN("Windows::ReadDirectoryChanges_asynchronous::WatchSubTree"
      "--address of p_readdirectorychangeswparameters:" <<
      p_readdirectorychangeswparameters
      << "address of p_readdirectorychangeswparameters->overlapped:"
      << & p_readdirectorychangeswparameters->overlapped)
    m_stdset_p_readdirectorychangeswparameters.insert(
      p_readdirectorychangeswparameters) ;
    p_readdirectorychangeswparameters->stdwstrRootPath = cr_stdwstrRootPath ;
    DWORD dw = StartWatch( * p_readdirectorychangeswparameters) ;
  ////  std::cout << "before CreateThread\n" ;
    HANDLE handleThread = ::CreateThread(
      NULL,                   // default security attributes
      0,                      // use default stack size
      WatchSubTree_asynchronousThreadProc ,       // thread function name
  //    (void *) //cast "const void *" to "void *"
  //    ( //address of std::tstring
  //      &
  //      (* //std::tstring
  //      //iterator
  //      stdpair.first)
  //    )
//      & m_s_fs_watch ,          // argument to thread function
      p_readdirectorychangeswparameters ,
      0,                      // use default creation flags
      & dwThreadId
      );   // returns the thread identifier
    if( handleThread )
      ::CloseHandle(handleThread) ;
    return dw ;
  }
//  std::cout << "after CreateThread\n" ;
  return 1 ;
}
