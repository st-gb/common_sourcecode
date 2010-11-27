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

class ReadDirectoryChangesWparameters
{
public:
  volatile bool bContinue ;
  BYTE arbyDataBuffer[READ_DIR_CHANGES_BUFFER_SIZE] ;
  HANDLE handleDirectory ;
  OVERLAPPED overlapped ;
  std::wstring stdwstrRootPath ;
  ReadDirectoryChangesWparameters()
    : bContinue( true )
  {
  }
} ;

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
  return handleDirectory ;
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
  dwCurrentOffset = 0;
  do
  {
    p_file_notify_information = (FILE_NOTIFY_INFORMATION * )(
      & arby[dwCurrentOffset] );
    file_or_dir_watch_info.m_byAction = p_file_notify_information->Action;
    file_or_dir_watch_info.m_dwFileNameLength = p_file_notify_information->
      FileNameLength;
    file_or_dir_watch_info.m_p_wchFileName = p_file_notify_information->FileName;
    file_or_dir_watch_info.m_p_wchRootPath = (wchar_t * )
      ( ps_fswatch->stdwstrRootPath.c_str() );
#ifdef COMPILE_WITH_LOG
    std::string stdstr ;
#endif //#ifdef COMPILE_WITH_LOG
    switch(file_or_dir_watch_info.m_byAction)
    {
    case FILE_ACTION_ADDED:
#ifdef COMPILE_WITH_LOG
      stdstr = "FILE_ACTION_ADDED" ;
#endif //#ifdef COMPILE_WITH_LOG
      break ;
    case FILE_ACTION_REMOVED:
#ifdef COMPILE_WITH_LOG
      stdstr = "FILE_ACTION_REMOVED" ;
#endif //#ifdef COMPILE_WITH_LOG
      break ;
    case FILE_ACTION_MODIFIED:
#ifdef COMPILE_WITH_LOG
      stdstr = "FILE_ACTION_MODIFIED" ;
#endif //#ifdef COMPILE_WITH_LOG
      break ;
    case FILE_ACTION_RENAMED_OLD_NAME:
      file_or_dir_watch_info.m_stdwstrOldFileOrDirPath = std::wstring(
        p_file_notify_information->FileName,
        p_file_notify_information->FileNameLength) ;
#ifdef COMPILE_WITH_LOG
      stdstr = "FILE_ACTION_RENAMED_OLD_NAME" ;
#endif //#ifdef COMPILE_WITH_LOG
      break ;
    case FILE_ACTION_RENAMED_NEW_NAME:
      file_or_dir_watch_info.m_stdwstrCurrentFileOrDirPath = std::wstring(
        p_file_notify_information->FileName,
        p_file_notify_information->FileNameLength) ;
#ifdef COMPILE_WITH_LOG
      stdstr = "FILE_ACTION_RENAMED_NEW_NAME" ;
#endif //#ifdef COMPILE_WITH_LOG
      break ;
    }
//#endif //#ifdef COMPILE_WITH_LOG
    LOGN("ProcessReadDirectoryChangesRecords--file name:" <<
      GetStdString_Inline( std::wstring( file_or_dir_watch_info.
        m_p_wchFileName ) )
      << "action:" << (WORD) file_or_dir_watch_info.m_byAction
      << "(" << stdstr << ")"
      )
    ( * ps_fswatch->pf_Callback) ( file_or_dir_watch_info);
    if(p_file_notify_information->NextEntryOffset == 0)
        break;

    dwCurrentOffset += p_file_notify_information->NextEntryOffset;
  }
  while(1) ;
}

#endif /* PROCESSREADDIRECTORYCHANGESRECORDS_HPP_ */
