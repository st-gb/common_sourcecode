/** File:   file_exists.h
 * Author: Tillmann
 * Created on 12. September 2017, 19:45 */

#ifndef FILE_EXISTS_H
#define FILE_EXISTS_H

#ifdef __unix__
  #include <OperatingSystem/POSIX/file_exists.hpp>
#endif
#ifdef _WIN32
  #include <Windows/FileSystem/file_exists.h>
#endif

#endif /* FILE_EXISTS_H */

