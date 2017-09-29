#pragma once /** include guard */

//http://ubuntuforums.org/showthread.php?t=889612
#include <inttypes.h> //int64_t
#include <string> //class std::string
#include <hardware/CPU/fastest_data_type.h> //fastestUnsignedDataType

/** Base class for native (regarding Operating System) file access. 
  Especially intended for getting error codes on failure in contrast to when
  using class std::ofstream. */
class I_File
{
protected:
  std::string m_filePathA;
public:
  typedef int64_t file_pointer_type;
  enum CloseError {closingFileSucceeded = 0, closingFileFailed, fileNotOpen};
  enum OpenError {success = 0, accessDenied, fileNotFound, not_set };
  enum OpenMode { readOnly, writeOnly, readAndWrite };
  enum ReadResult { successfullyRead, readLessThanIntended,
    endOfFileReached, unknownReadError };
  enum WriteResult { successfullyWritten = 0, unknownWriteError,
    BadFileDescriptor, /** E.g. file only opened for in read mode ("r") */
    FileExceedsMaxFileSize, NoFreeSpaceLeft};
  enum SeekResult {successfullySeeked = 0, notAseekableStream};

  virtual ~I_File() {};

  virtual bool IsOpen() const { return false;}
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
  /**@param bufferSizeInByte : in: buffer size to read    
   *         out: number of bytes actually read. */
  virtual enum ReadResult Read(
    uint8_t buffer [],
    fastestUnsignedDataType numberOfBytesToRead,
    fastestUnsignedDataType & numberOfBytesRead)
    { return unknownReadError;
    /*throw FileException("not implemented yet");*/ }
  //TODO provide error code on failure or throw an exception.
  virtual enum SeekResult SeekFilePointerPosition(const file_pointer_type &) = 0;
  virtual enum WriteResult Write(
    const unsigned char buffer[],
    const unsigned bufferSizeInByte) const
    { return unknownWriteError; }
};
