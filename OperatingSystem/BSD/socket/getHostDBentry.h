#pragma once///Include guard

/**Don't use sculp ("::") operator for function names here because this file may
 * be included from a C file compiled by a C compiler. C does not know "::". */

#include "gethostbyname.h"///gethostbyname(...), gethostbynameUnknownHost etc.

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#else
static///Needed for C
#endif
inline /*struct hostent **/ enum gethostbynameRslt GetHostDataBaseEntry(
  const char hostName [], struct hostent ** p_hostDataBaseEntry)
{
  /** https://linux.die.net/man/3/gethostbyname :
   * "The gethostbyname() and gethostbyaddr() functions return the hostent 
   * structure or a NULL pointer if an error occurs. On error, the h_errno 
   * variable holds an error number. When non-NULL, the return value may point
   * at static data, see the notes below. " */
  /*struct hostent **/ *p_hostDataBaseEntry = gethostbyname(hostName);
//#ifdef _DEBUG
//  if (p_hostDataBaseEntry == NULL) {
#ifdef _WIN32///If compiled under (also 64 bit) Microsoft Windows
 ///https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-gethostbyname
    const int lastWinSocketAPIerror = WSAGetLastError();
#endif
//#ifdef __linux__
  if(! *p_hostDataBaseEntry)
    ///https://linux.die.net/man/3/h_errno
    switch(h_errno)///Does Windows also have h_errno?
    {
      case HOST_NOT_FOUND :
      case NO_DATA: ///When host was not in database under Microsoft Windows.
        return gethostbynameUnknownHost;
      default:
        return gethostbynameOtherError;
    }
//  else
//#endif
//    LOGN_ERROR("host " << hostName << " not in database;error code:" << h_errno)
//  }
  return /*p_hostDataBaseEntry*/gethostbynameSucceeded;
}
#ifdef __cplusplus
}}}
#endif
