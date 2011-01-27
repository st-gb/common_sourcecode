/* 
 * File:   I_FileSystemEvents.hpp
 * Author: Stefan
 *
 * Created on 5. Oktober 2009, 14:48
 */

#ifndef _I_FILESYSTEMEVENTS_HPP
#define	_I_FILESYSTEMEVENTS_HPP

//#ifdef _WIN32
  #include <windef.h> //DWORD
//#else
//  #include <Windows_compatible_typedefs.h> //DWORD
//#endif
#include <string> //class std::string
#include <set> //class std::set
#include <Controller/character_string/stdtstr.hpp> //class std::tstring
#include <Attributes/FileOrDirWatchInfo.hpp> //class FileOrDirWatchInfo

class FileSystemEventException
{
public:
  FileSystemEventException(DWORD dw) {} 
};

typedef void ( * watch_handler )(
  //WCHAR * FileName,DWORD FileNameLength, DWORD Action
  FileOrDirWatchInfo & cr_fileordirwatchinfo
  ) ;

struct S_FSwatch
{
  volatile bool m_v_bWatch ;
  void ( * pf_Callback )(//WCHAR * FileName, DWORD FileNameLength, DWORD Action
      FileOrDirWatchInfo & r_fileordirwatchinfo) ;
//  std::tstring tstrRootPath ;
  std::wstring stdwstrRootPath ;
};

//Base class (least common denominator) for classes  that implement retrieving
//file systems events such as for inotify (Linux), wxFileSystemWatcher
//(wxWidgets), ReadDirectoryChangesW (Windows).
class I_FileSystemEvents
{
public:
  enum starting_watch_result
  {
    success ,
    failure
  };
  //implement destructor because else g++: "warning: `class I_FileSystemEvents'
  //has virtual functions but non-virtual destructor"
  virtual ~I_FileSystemEvents() {}
  std::set<std::tstring> m_stdset_stdtstrWatchedDir ;
  struct S_FSwatch m_s_fs_watch ;
  virtual bool IsBeingWatched(  const std::tstring & strRootPath )
    { return false ; }
  //Return value: success or failure.
  virtual //BYTE
    DWORD WatchSubTree(
//    const std::tstring & strRootPath ,
    const std::wstring & cr_stdwstrRootPath ,
//    void ( * callback )(WCHAR * FileName, DWORD FileNameLength, DWORD Action )
    watch_handler
    ) = 0 ;
//  void EndAllWatches()

  //Must be "virtual" if this method is overwritten in subclasses to be
  // callable.
  virtual void EndWatchSubTree(
    const std::wstring & cr_stdtstrRootPath)
  {
    m_s_fs_watch.m_v_bWatch = false ;
  }
  //Must be "virtual" if this method is overwritten in subclasses to be
  // callable.
  virtual void EndWatchSubTree()
  {
    m_s_fs_watch.m_v_bWatch = false ;
  }
  //virtual ~I_FileSystemEvents() {} ;
};

#endif	/* _I_FILESYSTEMEVENTS_HPP */
