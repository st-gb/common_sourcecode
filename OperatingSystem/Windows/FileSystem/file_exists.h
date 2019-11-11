/** File:   file_exists.h
 * Author: Tillmann
 * Created on 12. September 2017, 19:49 */

#ifndef WINDOWS_FILE_EXISTS_H
#define WINDOWS_FILE_EXISTS_H

#include <Shlwapi.h> //PathFileExists(...)

inline bool FileExists(const char *pathname)
{
  return PathFileExistsA(pathname);
}
#endif /* WINDOWS_FILE_EXISTS_H */

