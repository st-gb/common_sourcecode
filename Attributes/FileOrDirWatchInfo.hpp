/*
 * FileOrDirWatchInfo.hpp
 *
 *  Created on: Nov 20, 2010
 *      Author: Stefan
 */

#ifndef FILEORDIRWATCHINFO_HPP_
#define FILEORDIRWATCHINFO_HPP_

#include <string> //std::wstring

typedef unsigned char BYTE ;
typedef unsigned long DWORD ;

#include <ModelData/CFileChange.hpp>

////Forward decl.
//class CFileChange;

//Named "watch" and not "change" because not only changes are being tracked.
class FileOrDirWatchInfo
//class FileOrDirWatchAttributes
{
public:
//  enum changeType
//  {
//    //from MinGW's "include\winnt.h":
////  #define FILE_ACTION_ADDED                   0x00000001
////  #define FILE_ACTION_REMOVED                 0x00000002
////  #define FILE_ACTION_MODIFIED                0x00000003
////  #define FILE_ACTION_RENAMED_OLD_NAME        0x00000004
////  #define FILE_ACTION_RENAMED_NEW_NAME        0x00000005
//    added = 1,
//    removed,
//    modified,
//    renamed_old_name,
//    renamed_new_name
//  };
  BYTE m_byAction ;
  DWORD m_dwFileNameLength;
  wchar_t * m_p_wchFileName ;
  wchar_t * m_p_wchRootPath ;
  std::wstring m_stdwstrOldFileOrDirPath ;
  std::wstring m_stdwstrCurrentFileOrDirPath ;

  FileOrDirWatchInfo() {} //Default constructor.
  FileOrDirWatchInfo(
    BYTE byAction ,
//    DWORD m_dwFileNameLength ,
//    wchar_t * m_p_wchFileName ,
//    wchar_t * m_p_wchRootPath ,
    std::wstring & stdwstrCurrentFileOrDirPath ,
    std::wstring & stdwstrOldFileOrDirPath
    )
  {
    m_byAction = byAction ;
//    m_dwFileNameLength = dwFileNameLength ;
//    wchar_t * m_p_wchFileName ,
//    wchar_t * m_p_wchRootPath ,
    m_stdwstrCurrentFileOrDirPath = stdwstrCurrentFileOrDirPath ;
    m_stdwstrOldFileOrDirPath = stdwstrOldFileOrDirPath ;
  }
  CFileChange GetAsFileChange( DirWatchInfoBase * p_dirwatchinfobase) const
  {
    CString cstringCurrentFileOrDirPath(
      m_stdwstrCurrentFileOrDirPath) ;
    CString cstringOldFileOrDirPath(
      m_stdwstrOldFileOrDirPath ) ;
//  //      iterDestinations->second->Insert( cr_fileordirwatchattributes) ;
//      iterDestinations->second->DeleteIfExistant(
//        p_filechange, true ) ;
    CFileChange filechange(
//        m_stdwstrCurrentFileOrDirPath ,
      cstringCurrentFileOrDirPath ,
      m_byAction ,
      //const
  //    CDirWatchInfo * pDirWatchInfo,
//        DirWatchInfoBase * pDirWatchInfo,
//      this //,
      p_dirwatchinfobase
      //Is used for rename operations.
//        const CString * const cpcstrOldRelativeFileName = NULL
//        m_stdwstrOldFileOrDirPath
//        & cstringOldFileOrDirPath
      ) ;
    if( ! m_stdwstrOldFileOrDirPath.empty() )
      //If renamed then in the map stored path is the old file path now,
      //so search for this old path.
      filechange.m_strRelativePath =
        m_stdwstrOldFileOrDirPath ;
    return filechange;
  }
  CFileChange * GetAsDynAllocFileChange(
    DirWatchInfoBase * p_dirwatchinfobase) const
  {
    CString cstringCurrentFileOrDirPath(
      m_stdwstrCurrentFileOrDirPath) ;
    CString cstringOldFileOrDirPath(
      m_stdwstrOldFileOrDirPath ) ;
//  //      iterDestinations->second->Insert( cr_fileordirwatchattributes) ;
//      iterDestinations->second->DeleteIfExistant(
//        p_filechange, true ) ;
    CFileChange * p_filechange = new CFileChange(
//        m_stdwstrCurrentFileOrDirPath ,
      cstringCurrentFileOrDirPath ,
      m_byAction ,
      //const
  //    CDirWatchInfo * pDirWatchInfo,
//        DirWatchInfoBase * pDirWatchInfo,
//      this //,
      p_dirwatchinfobase
      //Is used for rename operations.
//        const CString * const cpcstrOldRelativeFileName = NULL
//        m_stdwstrOldFileOrDirPath
//        & cstringOldFileOrDirPath
      ) ;
//    if( ! m_stdwstrOldFileOrDirPath.empty() )
//      //If renamed then in the map stored path is the old file path now,
//      //so search for this old path.
//      p_filechange->m_strRelativePath =
//        m_stdwstrOldFileOrDirPath ;
    p_filechange->m_strOldRelativeFileOrDirPath = cstringOldFileOrDirPath;
    return p_filechange;
  }
} ;

#endif /* FILEORDIRWATCHINFO_HPP_ */
