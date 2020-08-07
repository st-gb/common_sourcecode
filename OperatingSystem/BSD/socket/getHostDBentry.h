#pragma once///Include guard

#include "gethostbyname.h"///gethostbyname(...)

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#else
static///Needed for C
#endif
inline struct hostent * GetHostDataBaseEntry(const char hostName [])
{
  /** https://linux.die.net/man/3/gethostbyname :
   * "The gethostbyname() and gethostbyaddr() functions return the hostent 
   * structure or a NULL pointer if an error occurs. On error, the h_errno 
   * variable holds an error number. When non-NULL, the return value may point
   * at static data, see the notes below. " */
  struct hostent * p_hostDataBaseEntry = gethostbyname(hostName);
//  if (p_hostDataBaseEntry == NULL) {
    //TODO check h_errno
//    LOGN_ERROR("host " << hostName << " not in database;error code:" << h_errno)
//  }
  return p_hostDataBaseEntry;
}
#ifdef __cplusplus
}}}
#endif
