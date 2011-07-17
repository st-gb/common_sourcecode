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
#include <map> //class std::map
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
//  void ( * pf_Callback )(//WCHAR * FileName, DWORD FileNameLength, DWORD Action
//      FileOrDirWatchInfo & r_fileordirwatchinfo) ;
  watch_handler pf_Callback;
//  std::tstring tstrRootPath ;
  std::wstring stdwstrRootPath ;
  S_FSwatch() {}
  S_FSwatch(
    watch_handler pf_Callback,
    const std::wstring & cr_std_wstrRootPath,
    bool bWatch
    )
  {
//    LOGN( FULL_FUNC_NAME << "pf_Callback:" << (void *) pf_Callback )
    this->pf_Callback = pf_Callback;
//    LOGN( FULL_FUNC_NAME << "this->pf_Callback:" << (void *) this->pf_Callback )
    stdwstrRootPath = cr_std_wstrRootPath;
    m_v_bWatch = bWatch;
  }
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
  std::map<std::wstring, struct S_FSwatch>
    m_std_map_std_wstringFSWrootPath2s_fs_watch;
  //TODO a NodeTrie should be faster.
//  NodeTrie m_nodetrieFSWrootPath2s_fs_watch( //pow(2.0, sizeof(wchar_t) * 8) )
//      )

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
  virtual //void
    BYTE EndWatchSubTree(
    const std::wstring & cr_stdtstrRootPath) = 0;
//  {
//    m_s_fs_watch.m_v_bWatch = false ;
//  }
//  //Must be "virtual" if this method is overwritten in subclasses to be
//  // callable.
//  virtual void EndWatchSubTree(
//      std::wstring & r_std_wstrMessage)
//  {
//    m_s_fs_watch.m_v_bWatch = false ;
//    r_std_wstrMessage = L"";
//  }
  //virtual ~I_FileSystemEvents() {} ;
};

#endif	/* _I_FILESYSTEMEVENTS_HPP */
