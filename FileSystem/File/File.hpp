#pragma once

//http://ubuntuforums.org/showthread.php?t=889612
#include <inttypes.h> //int64_t
#include <string> //class std::string

/** Base class for native (regarding Operating System) file access. 
  Especially intended for getting error codes on failure in contrast to when
  using class std::ofstream. */
class I_File
{
protected:
  std::string m_filePathA;
public:
  typedef int64_t file_pointer_type;
  enum CloseError {closingFileSucceeded = 0, closingFileFailed};
  enum OpenError {success = 0, accessDenied, fileNotFound, not_set };
  enum OpenMode { readOnly, writeOnly };
  enum ReadResult { successfullyRead = 0, readLessThanIntended, 
    endOfFileReached, unknownReadError };
  enum SeekResult {successfullySeeked = 0, notAseekableStream };

  virtual ~I_File() {};

  /** Open a file with an ANSI (= 8 bit) character file path. */
  virtual enum OpenError OpenA(const char * const, enum I_File::OpenMode openMode) = 0;
  std::string GetFilePathA() const { return m_filePathA; }
  //TODO maybe provide error code on failure or throw an exception.
  virtual file_pointer_type GetFileSizeInBytes() = 0;
  //TODO maybe provide error code on failure or throw an exception.
  virtual file_pointer_type GetCurrentFilePointerPosition() = 0;
  /** Read a single byte from the file. */
  //TODO maybe provide error code on failure or throw an exception.
  virtual int ReadByte() = 0;
  virtual enum ReadResult Read( unsigned char * buffer, unsigned 
    bufferSizeInByte) { return unknownReadError; 
    /*throw FileException("not implemented yet");*/ }
  //TODO provide error code on failure or throw an exception.
  virtual enum SeekResult SeekFilePointerPosition(const file_pointer_type &) = 0;
};
