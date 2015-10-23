#pragma once

#include <FileSystem/File/File.hpp> //base class I_File
#include <stdio.h>
#include <string> //class std::string
#include <errno.h> //ESUCCESS, EACCESS

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
      //_ftelli64
      return currentFilePos;
    }
    file_pointer_type GetFileSizeInBytes()
    {
      fseek(m_pFile, 0, SEEK_END);
      file_pointer_type fileSize = ftell(m_pFile);
      return fileSize;
    }
	
	enum CloseError Close()
	{
	  const int retVal = fclose(m_pFile);
	  /** http://www.cplusplus.com/reference/cstdio/fclose/: 
	    "If the stream is successfully closed, a zero value is returned."
		"On failure, EOF is returned." */
      if( retVal == 0)
	    return closingFileSucceeded;
      return closingFileFailed;
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
	  const int i = fgetc(m_pFile);
	  /**http://pubs.opengroup.org/onlinepubs/009695399/functions/fgetc.html
	  * "If the end-of-file indicator for the stream is set, or if the stream 
	  * is at end-of-file, the end-of-file indicator for the stream shall be set 
	  * and fgetc() shall return EOF. If a read error occurs, the error indicator 
	  * for the stream shall be set, fgetc() shall return EOF, 
	  * [CX] [Option Start]  and shall set errno to indicate the error." */
	  if( i == EOF )
	  {
               // g++: "error: ‘ESUCCESS’ was not declared in this scope"
		/*if( errno == ESUCCESS)
		  return I_File::endOfFileReached;
		else*/
		  return I_File::unknownReadError;
	  }
      return I_File::successfullyRead;
    }

    enum ReadResult Read( unsigned char * buffer, unsigned bufferSizeInByte) 
    {
      const size_t numElesRead = fread(buffer, 
        //From http://www.cplusplus.com/reference/cstdio/fread/
        1, /** "Size, in bytes, of each element to be read."*/
        /** Number of elements, each one with a size of size bytes. */
        bufferSizeInByte,
        m_pFile);
        //ferror(m_pFile)
      if( numElesRead == bufferSizeInByte)
        return successfullyRead;
      return unknownReadError;
    }

    enum SeekResult SeekFilePointerPosition(const file_pointer_type & filePos)
    {
      /** http://pubs.opengroup.org/onlinepubs/009696899/functions/fseek.html:
      * "The fseek() [CX] [Option Start]  and fseeko() [Option End] functions
      * shall return 0 if they succeed. */
      const int retVal = /*fseek*/fseeko64(m_pFile, filePos, SEEK_SET);
      if(retVal == 0) return successfullySeeked;
      //TODO provide proper error code on failure.
      /*switch( errno )
      {
        case notAseekableStream;
      }*/
      return notAseekableStream;
    }
  };/** class File*/
}/** namespace Linux */

