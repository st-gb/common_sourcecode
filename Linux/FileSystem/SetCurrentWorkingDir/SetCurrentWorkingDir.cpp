#include <Controller/FileSystem/SetCurrentWorkingDir.hpp>
#include "SetCurrentWorkingDir.hpp"

//extern "C"
//{
  int SetCurrentDirectory(//std::string & r_stdstr
    const char * pchCurrentWorkingDir)
  {
    return SetCurrentWorkingDir_inl(pchCurrentWorkingDir);
  }
//}
