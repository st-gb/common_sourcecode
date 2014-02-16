#pragma once

//http://ubuntuforums.org/showthread.php?t=889612
#include <inttypes.h> //int64_t

/** Base class for native (regarding Operating System) file access. 
  Especially intended for getting error codes on failure in contrast to when
  using class std::ofstream. */
class I_File
{
public:
  typedef int64_t file_pointer_type;
  enum OpenError {success = 0, accessDenied, fileNotFound, not_set };
  enum OpenMode { readOnly, writeOnly };
  
  virtual ~I_File() {};
  /** Open a file with an ANSI (= 8 bit) character file path. */
  virtual enum OpenError OpenA(const char * const, enum I_File::OpenMode openMode) = 0;
  virtual file_pointer_type GetFileSizeInBytes() = 0;
  virtual file_pointer_type GetCurrentFilePointerPosition() = 0;
  /** Read a single byte from the file. */
  virtual int ReadByte() = 0;
  virtual bool SeekFilePointerPosition(const file_pointer_type &) = 0;
};