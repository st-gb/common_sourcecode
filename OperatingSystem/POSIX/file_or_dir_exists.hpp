/** File:   file_or_dir_exists.hpp
 * Author: sg
 * Created on 21. August 2017, 22:01  */

#ifndef FILE_OR_DIR_EXISTS_HPP
#define FILE_OR_DIR_EXISTS_HPP

#include <sys/stat.h> //stat(...)

namespace POSIX
{
  bool file_or_dir_exists(const char const *)
  {
    //from https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c-cross-platform
    struct stat   buffer;   
    return (stat (filename, &buffer) == 0); 
  }
}

#endif /* FILE_OR_DIR_EXISTS_HPP */

