/* 
 * File:   ReadDirectoryChanges_synchronous.hpp
 * Author: Stefan
 *
 * Created on 11. Dezember 2009, 13:10
 */

#ifndef _READDIRECTORYCHANGES_HPP
#define	_READDIRECTORYCHANGES_HPP

#include <Controller/FileSystem/I_FileSystemEvents.hpp>//base class

namespace Windows
{
  class ReadDirectoryChanges_synchronous
    : public I_FileSystemEvents
  {
  public:
  //  void EndWatchSubTree() ;
    ReadDirectoryChanges_synchronous();
    ReadDirectoryChanges_synchronous(const ReadDirectoryChanges_synchronous& orig);
    virtual ~ReadDirectoryChanges_synchronous();
    //BYTE
    DWORD WatchSubTree(
      const std::tstring & strRootPath ,
  //    const std::wstring & cr_stdwstrRootPath ,
      //Function pointer.
  //    void (*callback)(WCHAR * FileName, DWORD FileNameLength, DWORD Action )
      watch_handler
      ) ;
  private:
  };
}

#endif	/* _READDIRECTORYCHANGES_HPP */

