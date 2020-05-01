#pragma once///Include guard

#ifdef __cplusplus///enable both C and C++ 
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

enum GetSocketTimeoutRslt{success, getRcvTimeoutError, getSndTimeoutError,
  getRcvAndSndTimeoutError};

///Use pointer ("*") rather than reference ("&") to avoid to enable C usage.
int getSocketTimeout(const int socketFileDesc, 
  struct timeval * timevalSocketTimeout, const int optName);
int setSocketTimeout(const int socketFileDesc, 
  struct timeval * p_timevalSocketTimeout, const int optName);
GetSocketTimeoutRslt GetSocketTimeoutInS(const int socketFileDesc, double * s);

#ifdef __cplusplus///enable both C and C++ 
}}}///end namespaces
#endif
