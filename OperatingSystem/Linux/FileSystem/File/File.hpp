#pragma once

#include <FileSystem/File/File.hpp> //base class I_File
#include <FileSystem/File/FileReadException.hpp>
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
    File() : m_pFile(0) { }
    ~File() { if( IsOpen() ) Close(); }
    
    file_pointer_type GetCurrentFilePointerPosition()
    {
      //TODO data type of ftell(): "long" has same size as CPU architecture:
      // if 32 bit CPU, then 32 bit data type-> max. file size reported is
      // ~ "2^32 / 2 - 1"
      file_pointer_type currentFilePos =
#ifdef ANDROID //Android does not know "ftello64"
        ftell(m_pFile);
#else
        ftello64(m_pFile);
#endif
      //_ftelli64
      return currentFilePos;
    }
    file_pointer_type GetFileSizeInBytes()
    {
      /** Use 64 bit file offsets in order to support file sizes > 4GB */
#ifdef ANDROID //Android does not know "fseeko64"
      fseek(m_pFile, 0, SEEK_END);
#else
      fseeko64(m_pFile, 0, SEEK_END);
#endif
#ifdef __ANDROID__ //Android does not know "ftello64"
      file_pointer_type fileSize = ftello(m_pFile);
#else
      file_pointer_type fileSize = ftello64(m_pFile);
#endif
      return fileSize;
    }
	
    enum CloseError Close()
    {
      if( m_pFile)
      {
        const int retVal = fclose(m_pFile);
        /** http://www.cplusplus.com/reference/cstdio/fclose/:
        "If the stream is successfully closed, a zero value is returned."
        "On failure, EOF is returned." */
        if( retVal == 0)
        {
          m_pFile = NULL;
          return closingFileSucceeded;
        }
        return closingFileFailed;
      }
      return closingFileFailed;
    }
	
//	ErrnoTo
    bool IsOpen() const
    {
      return m_pFile != NULL;
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
      case I_File::writeOnly:
        fopenOpenMode = "w";
        break;
      case I_File::readAndWrite:
        /** http://www.gnu.org/software/libc/manual/html_node/Opening-Streams.html
        "Open an existing file for both reading and writing. The initial
        contents of the file are unchanged and the initial file position is at
        the beginning of the file." */
        fopenOpenMode = "r+";
        break;
      }
      /**http://stackoverflow.com/questions/15753090/c-fopen-fails-for-write-with-errno-is-2
       * http://www.gnu.org/software/libc/manual/html_node/File-Positioning.html :
       *  must use fopen64, freopen64, or tmpfile64 for "ftello64" */
#ifdef ANDROID //Android does not know "fopen64"
      m_pFile = fopen(filePath , fopenOpenMode.c_str() );
#else
      m_pFile = fopen64(filePath , fopenOpenMode.c_str() );
#endif
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
        //return I_File::unknownReadError;
        FileReadException fileReadException(
          I_File::unknownReadError,
          /*osErrorCode*/ errno, m_filePathA.c_str () );
	    throw fileReadException;
	  }
      return /*I_File::successfullyRead*/ i;
    }

    enum ReadResult Read(
      uint8_t buffer[], 
      fastestUnsignedDataType numberOfBytesToRead, 
      fastestUnsignedDataType & numberOfBytesRead)
    {
      const size_t numElesRead = fread(buffer, 
        //From http://www.cplusplus.com/reference/cstdio/fread/
        1, /** "Size, in bytes, of each element to be read."*/
        /** Number of elements, each one with a size of size bytes. */
        numberOfBytesToRead,
        m_pFile);
//      switch(errno)
//      {
//        case EACCESS:
//      }
#ifdef _DEBUG
      if( numberOfBytesToRead != numElesRead)
      {
      int result = feof(m_pFile);
      result = ferror(m_pFile);
      }
#endif
      if( numElesRead < numberOfBytesToRead)
        return readLessThanIntended;
        //ferror(m_pFile)
      if( numElesRead == numberOfBytesToRead)
        return successfullyRead;
      return unknownReadError;
    }

    enum SeekResult SeekFilePointerPosition(const file_pointer_type & filePos)
    {
      /** http://pubs.opengroup.org/onlinepubs/009696899/functions/fseek.html:
      * "The fseek() [CX] [Option Start]  and fseeko() [Option End] functions
      * shall return 0 if they succeed. */
      //TODO recognize seek failures (can't be determined according to the re
      // return value of fseek or errno
#ifdef ANDROID //Android does not know "fseeko64"
      const int retVal = fseek(m_pFile, filePos, SEEK_SET);
#else
      const int retVal = /*fseek*/fseeko64(m_pFile, filePos, SEEK_SET);
#endif
#ifdef _DEBUG
      int errCode = errno;
#endif //#ifdef _DEBUG
      if(retVal == 0) return successfullySeeked;
      //TODO provide proper error code on failure.
      /*switch( errno )
      {
        case notAseekableStream;
      }*/
      return notAseekableStream;
    }

    enum WriteResult Write(
      const unsigned char buffer[],
      const unsigned bufferSizeInByte) const
    {
      const size_t numElesWritten = fwrite(buffer,
        //From http://www.cplusplus.com/reference/cstdio/fread/
        1, /** "Size, in bytes, of each element to be read."*/
        /** Number of elements, each one with a size of size bytes. */
        bufferSizeInByte,
        m_pFile);
        //ferror(m_pFile)
      if( numElesWritten == bufferSizeInByte)
        return successfullyWritten;
      /** @see http://pubs.opengroup.org/onlinepubs/009695399/functions/fputc.html */
      switch(errno )
      {
      case EBADF :
        return BadFileDescriptor;
      }
      return unknownWriteError;
    }
  };/** class File*/
}/** namespace Linux */
