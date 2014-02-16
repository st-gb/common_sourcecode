#pragma once

#include <FileSystem/File/File.hpp> //base class I_File
#include <stdio.h>
#include <string> //class std::string
#include <errno.h>

namespace Linux
{
  class File
    : public I_File
  {
    FILE * m_pFile;
  public:
    file_pointer_type GetCurrentFilePointerPosition()
    {
      //TODO data type of ftell(): "long" has same size as CPU architecture:
      // if 32 bit CPU, then 32 bit data type-> max. file size reported is
      // ~ "2^32 / 2 - 1"
      file_pointer_type currentFilePos = ftell(m_pFile);
      return currentFilePos;
    }
    file_pointer_type GetFileSizeInBytes()
    {
      fseek(m_pFile, 0, SEEK_END);
      file_pointer_type fileSize = ftell(m_pFile);
      return fileSize;
    }
    enum OpenError OpenA(const char * const filePath, enum I_File::OpenMode openMode)
    {
      enum I_File::OpenError openError = I_File::not_set;
      std::string fopenOpenMode;
      switch(openMode)
      {
      case I_File::readOnly:
        fopenOpenMode = "r";
        break;
      }
      //http://stackoverflow.com/questions/15753090/c-fopen-fails-for-write-with-errno-is-2
      m_pFile = fopen(filePath , fopenOpenMode.c_str() );
      if( m_pFile)
      {
        openError = I_File::success;
      }
      else
      {
        switch( errno)
        {
        //http://www.convirture.com/forums/viewtopic.php?f=36&t=2021
        case EACCES:
          openError = I_File::accessDenied;
          break;
        //http://man7.org/linux/man-pages/man3/errno.3.html
        case ENOENT:
          openError = I_File::fileNotFound;
          break;
        }
      }
      return openError;
    }
    int ReadByte()
    {
      return fgetc(m_pFile);
    }
    bool SeekFilePointerPosition(const file_pointer_type & filePos)
    {
      /** http://pubs.opengroup.org/onlinepubs/009696899/functions/fseek.html:
      * "The fseek() [CX] [Option Start]  and fseeko() [Option End] functions
      * shall return 0 if they succeed. */
      const int retVal = fseek(m_pFile, filePos, SEEK_SET);
      //TODO provide error code on failure.
      return retVal == 0;
    }
  };
}
