/*
 * ReadDirectoryChanges_asynchronous.hpp
 *
 *  Created on: Nov 19, 2010
 *      Author: Stefan
 */

#ifndef READDIRECTORYCHANGES_ASYNCHRONOUS_HPP_
#define READDIRECTORYCHANGES_ASYNCHRONOUS_HPP_

#include <Controller/FileSystem/I_FileSystemEvents.hpp>//base class
#include <set> //std::set
//class ReadDirectoryChangesWparameters ;
#include "../ProcessReadDirectoryChangesRecords.hpp"

namespace Windows
{
  class ReadDirectoryChanges_asynchronous
    : public I_FileSystemEvents
  {
    std::set<ReadDirectoryChangesWparameters *>
      m_stdset_p_readdirectorychangeswparameters ;
  public:
    void EndWatchSubTree(const std::wstring & cr_stdtstrRootPath)
    {
      std::set<ReadDirectoryChangesWparameters *>::iterator
        iter_stdset_p_readdirectorychangeswparameters =
        m_stdset_p_readdirectorychangeswparameters.begin() ;
      for( ; iter_stdset_p_readdirectorychangeswparameters !=
          m_stdset_p_readdirectorychangeswparameters.end() ;
        ++ iter_stdset_p_readdirectorychangeswparameters )
      {
        if( (*iter_stdset_p_readdirectorychangeswparameters)->stdwstrRootPath
            == cr_stdtstrRootPath
          )
        {
          //End watch
          (*iter_stdset_p_readdirectorychangeswparameters)->bContinue = false ;
          //Let continue after WaitForSingleObjectEx(...)
          ::SetEvent( (*iter_stdset_p_readdirectorychangeswparameters)->
            overlapped.hEvent ) ;
        }
      }
    }
//    ReadDirectoryChanges_asynchronous();
//    ReadDirectoryChanges_asynchronous(const ReadDirectoryChanges_asynchronous& orig);
//    virtual ~ReadDirectoryChanges_asynchronous();
    BYTE WatchSubTree(
      const std::tstring & strRootPath ,
  //    const std::wstring & cr_stdwstrRootPath ,
      //Function pointer.
  //    void (*callback)(WCHAR * FileName, DWORD FileNameLength, DWORD Action )
      watch_handler
      ) ;
    ~ReadDirectoryChanges_asynchronous()
    {
      std::set<ReadDirectoryChangesWparameters *>::iterator
        iter_stdset_p_readdirectorychangeswparameters =
        m_stdset_p_readdirectorychangeswparameters.begin() ;
      for( ; iter_stdset_p_readdirectorychangeswparameters !=
          m_stdset_p_readdirectorychangeswparameters.end() ;
        ++ iter_stdset_p_readdirectorychangeswparameters )
      {
        //end watch
        (*iter_stdset_p_readdirectorychangeswparameters)->bContinue = false ;
        //Let continue after WaitForSingleObjectEx(...)
        ::SetEvent( (*iter_stdset_p_readdirectorychangeswparameters)->
          overlapped.hEvent ) ;
      }
    }
  private:

  };
}

#endif /* READDIRECTORYCHANGES_ASYNCHRONOUS_HPP_ */
