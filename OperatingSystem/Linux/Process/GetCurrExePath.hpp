#pragma once///Include guard

#ifdef __cplusplus
namespace OperatingSystem{namespace Process{
#endif

inline bool GetCurrExePath(std::string & currExePath){
  bool success = false;
  ///https://stackoverflow.com/questions/7051844/how-to-find-the-full-path-of-the-c-linux-program-from-within
  char procFSpath[20];
  char exepath[PATH_MAX + 1] = {0};
  sprintf(procFSpath, "/proc/%d/exe", getpid() );
  ///https://linux.die.net/man/2/readlink: "On error, -1 is returned"
  const ssize_t retVal = readlink(procFSpath, exepath, 1024 );
  if(retVal != -1){
    success = true;
    currExePath = exepath;
  }
  return success;
}

#ifdef __cplusplus
}}///namespaces
#endif
