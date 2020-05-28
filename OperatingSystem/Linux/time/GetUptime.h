#pragma once///Include guard

#include <time.h>///clock_gettime(...), CLOCK_MONOTONIC
///#include <.../OperSysNSname>///#define OperatingSystem

#ifdef __cplusplus
namespace OperatingSystem{
 template <typename uptimeInNsType>
 ///Make inline because only 1 function call->does not save a ot of space.
 inline
#endif
 bool GetUptimeInNs(//long double
  ///if C: typedef uptimeInNsType before including this file.
  uptimeInNsType & upTimeInNs)
{
  struct timespec s_timespec;
  /**http://www.opengroup.org/onlinepubs/9699919799/functions/gettimeofday.html:
  * "Applications should use the clock_gettime() function instead of the
  *  obsolescent gettimeofday() function." */
  /** Link to "librt" for "clock_gettime" */
  int ret = clock_gettime(
    /** from http://linux.die.net/man/3/clock_gettime:
    * "CLOCK_MONOTONIC: Clock that cannot be set and represents monotonic time
    * since some unspecified starting point."
    * Use CLOCK_MONOTONIC because this cannot be changed and so a time
    * difference can be calculated more safely. */
    CLOCK_MONOTONIC //clockid_t clock_id
    , & s_timespec //struct timespec *tp
    );
  upTimeInNs = (uptimeInNsType) s_timespec.tv_sec * 
    1000000000 + s_timespec.tv_nsec;
  return ret == 0;
}

#ifdef __cplusplus
 template <typename uptimeInS_Type> inline
#else /**If C: needs before including this file:
 * -typedef uptimeInS_Type: should be a floating point type to cover positions 
    after decimal point.
 * -typedef uptimeInNsType */
#endif
bool GetUptimeInS(uptimeInS_Type & upTimeInS)
{
  /*uptimeInNsType*/ double uptimeInNs;
  bool success = GetUptimeInNs(uptimeInNs);
  upTimeInS = (uptimeInS_Type)uptimeInNs/(uptimeInS_Type)1000000000;
  return success;
}
#ifdef __cplusplus
}///end namespace
#endif
