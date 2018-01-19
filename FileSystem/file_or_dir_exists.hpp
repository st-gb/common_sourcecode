/** File:   file_or_dir_exists.hpp
 * Author: sg
 * Created on 21. August 2017, 22:15  */

#ifndef FILE_OR_DIR_EXISTS_HPP
#define FILE_OR_DIR_EXISTS_HPP

#ifdef __linux__
  #include <OperatingSystem/POSIX/file_exists.hpp>
#endif

#ifdef __cplusplus
namespace FileSystem {
//extern "C" {
#endif
  
  bool file_or_dir_exists(const char *);

#ifdef __cplusplus
}
#endif

#endif /* FILE_OR_DIR_EXISTS_HPP */

