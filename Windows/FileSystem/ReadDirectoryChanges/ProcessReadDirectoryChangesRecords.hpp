/*
 * ProcessReadDirectoryChangesRecords.hpp
 *
 *  Created on: Nov 19, 2010
 *      Author: Stefan
 */

#ifndef PROCESSREADDIRECTORYCHANGESRECORDS_HPP_
#define PROCESSREADDIRECTORYCHANGESRECORDS_HPP_

#define READ_DIR_CHANGES_BUFFER_SIZE 64000L

#include <Controller/FileSystem/I_FileSystemEvents.hpp>//base class
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
//class FileOrDirWatchInfo ;

#ifdef COMPILE_WITH_LOG
  extern std::string g_ar_stdstrFileActions [] ;
#endif //#ifdef COMPILE_WITH_LOG

class ReadDirectoryChangesWparameters
{
public:
  volatile bool bContinue ;
  BYTE arbyDataBuffer[READ_DIR_CHANGES_BUFFER_SIZE] ;
  HANDLE handleDirectory ;
  HANDLE m_handleEventStopWatch;
  OVERLAPPED overlapped ;
  std::wstring stdwstrRootPath ;
  ReadDirectoryChangesWparameters()
    : bContinue( true )
  {
    m_handleEventStopWatch = ::CreateEvent(
      NULL,    // default security attribute
      TRUE,    // manual reset event
//      TRUE, // initial state = signaled
      FALSE, // FALSE=initial state = non-signaled
      NULL // NULL=unnamed event object
      );
  }
} ;

namespace Windows
{
  namespace ReadDirectoryChangesW
  {
    inline HANDLE GetHandleToDirectory(//struct S_FSwatch * ps_fswatch
      const std::wstring & cr_stdwstrRootPath,
      bool bAsynchronous = false)
    {
      HANDLE handleDirectory =
        //::CreateFile(
        ::CreateFileW(
        //tstrRootPath.c_str()
    //    ps_fswatch->tstrRootPath.c_str() , //__in      LPCTSTR lpFileName,
    //    ps_fswatch->stdwstrRootPath.c_str() , //__in      LPCTSTR lpFileName,
        cr_stdwstrRootPath.c_str() ,
        GENERIC_READ |
        //http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx:
        //(ReadDirectoryChangesW(...) )
        //"This directory must be opened with the FILE_LIST_DIRECTORY access right."
        FILE_LIST_DIRECTORY , //__in      DWORD dwDesiredAccess,
        //FILE_SHARE_DELETE |
        FILE_SHARE_READ | FILE_SHARE_WRITE ,//__in      DWORD dwShareMode,
        //http://msdn.microsoft.com/en-us/library/aa363858(VS.85).aspx:
        //"This parameter can be NULL."
        NULL , //__in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        OPEN_EXISTING ,//__in      DWORD dwCreationDisposition,
        //__in      DWORD dwFlagsAndAttributes
        //http://msdn.microsoft.com/en-us/library/aa365465%28VS.85%29.aspx
        //ReadDirectoryChangesW:
        //"To obtain a handle to a directory, use the CreateFile function with
        //the FILE_FLAG_BACKUP_SEMANTICS flag."
        bAsynchronous ? ( FILE_FLAG_BACKUP_SEMANTICS |
          //"To specify asynchronous completion, open the directory with CreateFile
          //as shown above, but additionally specify the FILE_FLAG_OVERLAPPED
          //attribute in the dwFlagsAndAttributes parameter."
          FILE_FLAG_OVERLAPPED )
          : FILE_FLAG_BACKUP_SEMANTICS,
        NULL //__in_opt  HANDLE hTemplateFile
        );
      LOGN("Windows::ReadDirectoryChangesW::GetHandleToDirectory(...)"
          "--handleDirectory: " << handleDirectory )
      return handleDirectory ;
    }
  }
}

inline void ProcessReadDirectoryChangesRecords(
  DWORD dwCurrentOffset,
  FILE_NOTIFY_INFORMATION * p_file_notify_information,
  BYTE arby[READ_DIR_CHANGES_BUFFER_SIZE],
  FileOrDirWatchInfo & file_or_dir_watch_info,
  struct S_FSwatch * ps_fswatch
  )
{
  LOGN("ProcessReadDirectoryChangesRecords begin")
  static BYTE byPreviousAction = 0;
  static bool bProcess = true ;
  bProcess = true ;
  dwCurrentOffset = 0;
  do
  {
    p_file_notify_information = (FILE_NOTIFY_INFORMATION * )(
      & arby[dwCurrentOffset] );
    //Make a copy because the buffer is overwritten the next
    //time.
    file_or_dir_watch_info.m_byAction = p_file_notify_information->Action;
//    file_or_dir_watch_info.m_dwFileNameLength = p_file_notify_information->
//      FileNameLength;
//    file_or_dir_watch_info.m_p_wchFileName = p_file_notify_information->FileName;
    file_or_dir_watch_info.m_p_wchRootPath = (wchar_t * )
      ( ps_fswatch->stdwstrRootPath.c_str() );
    LOGN("ProcessReadDirectoryChangesRecords--current entry: filename length:"
      << p_file_notify_information->FileNameLength )
#ifdef COMPILE_WITH_LOG
    std::string stdstr ;
#endif //#ifdef COMPILE_WITH_LOG
    switch( file_or_dir_watch_info.m_byAction )
    {
    case FILE_ACTION_MODIFIED:
      //A "modified" action occurs immediately after a rename: do not process
      //it.
      if( byPreviousAction == FILE_ACTION_RENAMED_NEW_NAME )
        bProcess = false ;
      break ;
    case FILE_ACTION_ADDED:
    case FILE_ACTION_REMOVED:
    case FILE_ACTION_RENAMED_NEW_NAME:
      //Make a copy of the strings because the buffer is overwritten the next
      //time.
      file_or_dir_watch_info.m_stdwstrCurrentFileOrDirPath = std::wstring(
        p_file_notify_information->FileName,
        //Length is in byte? -> 2 bytes per wide character.
        p_file_notify_information->FileNameLength / 2) ;
//      m_stdwstrOldFileOrDirPath
    } //switch
#ifdef COMPILE_WITH_LOG
    stdstr = g_ar_stdstrFileActions[file_or_dir_watch_info.m_byAction] ;
#endif //#ifdef COMPILE_WITH_LOG
    switch(file_or_dir_watch_info.m_byAction)
    {
    case FILE_ACTION_ADDED:
    case FILE_ACTION_REMOVED:
    case FILE_ACTION_MODIFIED:
      break ;
    case FILE_ACTION_RENAMED_OLD_NAME:
      //Make a copy of the strings because the buffer is overwritten the next
      //time.
      file_or_dir_watch_info.m_stdwstrOldFileOrDirPath = std::wstring(
        p_file_notify_information->FileName,
        //Length is in byte? -> 2 bytes per wide character.
        p_file_notify_information->FileNameLength / 2 ) ;
      file_or_dir_watch_info.m_stdwstrCurrentFileOrDirPath = L"" ;

//      if( p_file_notify_information->NextEntryOffset == 0)
//        break;
//      else //a FILE_ACTION_RENAMED_NEW_NAME entry should follow.
//      {
//        dwCurrentOffset += p_file_notify_information->NextEntryOffset;
//        p_file_notify_information = (FILE_NOTIFY_INFORMATION * )(
//          & arby[dwCurrentOffset] );
//        file_or_dir_watch_info.m_dwFileNameLength = p_file_notify_information->
//          FileNameLength;
//        file_or_dir_watch_info.m_p_wchFileName = p_file_notify_information->
//            FileName;
//        continue ;
//      }
      break ;
    case FILE_ACTION_RENAMED_NEW_NAME:
//      file_or_dir_watch_info.m_stdwstrCurrentFileOrDirPath = std::wstring(
//        p_file_notify_information->FileName,
//        p_file_notify_information->FileNameLength) ;
      break ;
    } //switch
//#endif //#ifdef COMPILE_WITH_LOG
    LOGN("ProcessReadDirectoryChangesRecords--current file name:\""
      << GetStdString_Inline( //std::wstring( file_or_dir_watch_info.
        //m_p_wchFileName )
        file_or_dir_watch_info.m_stdwstrCurrentFileOrDirPath
      )
      << "\" old file name:\"" << GetStdString_Inline( file_or_dir_watch_info.
        m_stdwstrOldFileOrDirPath)
      << "\" action:" << (WORD) file_or_dir_watch_info.m_byAction
      << "(" << stdstr << ")"
      )

    ( * ps_fswatch->pf_Callback) ( file_or_dir_watch_info);

    if( p_file_notify_information->NextEntryOffset == 0)
        break;
    dwCurrentOffset += p_file_notify_information->NextEntryOffset;
    byPreviousAction = file_or_dir_watch_info.m_byAction ;
  }
  while(1) ;
}

#endif /* PROCESSREADDIRECTORYCHANGESRECORDS_HPP_ */
