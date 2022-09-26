///(c)from 2020:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.01May2020 by Stefan Gebauer(TU Berlin matriculation number 361095)

#include <unistd.h>///socklen_t

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "socket.h"///SOL_SOCKET,setsockopt(...),getsockopt(...)
#include "socketTimeout.h"///enum GetSocketTimeoutRslt

TU_Bln361095BSDsktNmSpcBgn

int setSocketTimeout(
  const int socketFileDesc,
  ///Linux Mint 19:If sec and usec are 0 the operation times out after ca. 90 s.
  struct timeval * p_tvSocketTimeout,///Use pointer to enable C usage
  const int optName/**SO_RCVTIMEO, SO_SNDTIMEO*/)
{
  socklen_t optionLen = sizeof(*p_tvSocketTimeout);
  /**For other ideas see 
  http://stackoverflow.com/questions/4181784/how-to-set-socket-timeout-in-c-when-making-multiple-connections
   *int timeout=10000;setsockopt(socketFD,6,18,(char*)&timeout,sizeof(int));*/
  int returnValue =
    /**https://linux.die.net/man/2/setsockopt :"On success, zero is returned.
     * On error, -1 is returned, and errno is set appropriately."*/
    setsockopt(socketFileDesc, SOL_SOCKET, optName, 
    /** https://linux.die.net/man/7/socket "SO_RCVTIMEO and SO_SNDTIMEO
    * Specify the receiving or sending timeouts until reporting an error. 
    * The argument is a struct timeval. [...] If the timeout is set to zero (the
    * default) then the operation will never timeout."*/
    /** Linux:setting timeout to 1 microsecond let the value get 4000 
    * microseconds (got via getsocketopt(...))".*/
    /*(void *)*/ (const char *) p_tvSocketTimeout,
    /** https://linux.die.net/man/2/getsockopt : "The arguments optval and 
     * optlen are used to access option values for setsockopt()." */
    optionLen);
  #ifdef _DEBUG
  if(returnValue < 0)
  {///Needs WSAGetLastError() under Windows.
//    const int lastSockErrorCode = OperatingSystem::GetLastSocketErrorCode();
//    std::string st = OperatingSystem::GetSocketErrorMsg(lastSockErrorCode);
  }
  #endif
  return returnValue;///return errno instead?
}

int getSocketTimeout(
  const int socketFileDesc, 
  ///Linux Mint 19:If sec and usec are 0 the operation times out after ca. 90 s.
  struct timeval * p_tvSocketTimeout,///Use pointer to enable C usage
  const int optName/**SO_RCVTIMEO, SO_SNDTIMEO*/)
{
  socklen_t optionLen = sizeof(*p_tvSocketTimeout);
  int returnValue =
    /**https://linux.die.net/man/2/getsockopt :"On success, zero is returned.
     * On error, -1 is returned, and errno is set appropriately."*/
    getsockopt(socketFileDesc, SOL_SOCKET, optName, 
    /** https://linux.die.net/man/7/socket :"SO_RCVTIMEO and SO_SNDTIMEO
    * Specify the receiving or sending timeouts until reporting an error. 
    * The argument is a struct timeval. [...] If the timeout is set to zero (the
    * default) then the operation will never timeout."*/
    /*(void *)*/ (char*) p_tvSocketTimeout,
    /** https://linux.die.net/man/2/getsockopt : 
     * "For getsockopt(), optlen is a value-result argument, initially 
     * containing the size of the buffer pointed to by optval, and modified on 
     * return to indicate the actual size of the value returned." */
    & optionLen );
  #ifdef _DEBUG
  if(returnValue < 0)
  {///Needs WSAGetLastError() under Windows.
//    const int lastSocketErrorCode = OperatingSystem::GetLastSocketErrorCode();
//    std::string st = OperatingSystem::GetSocketErrMsg(lastSocketerrorCode);
  }
  #endif
  return returnValue;
}

inline void assign(double * p_timeoutInS, struct timeval * p_socketTimeout){
  * p_timeoutInS = p_socketTimeout->tv_sec;
  * p_timeoutInS += (double) p_socketTimeout->tv_usec/1000000.0;
}

enum GetSocketTimeoutRslt GetSocketTimeoutInS(const int socketFileDesc, 
  double * p_timeoutInS )
{
  enum GetSocketTimeoutRslt getSocketTimeoutRslt = success;
  struct timeval rcvSocketTimeout;
  struct timeval sendSocketTimeout;
  const int rcvToutRetVal = getSocketTimeout(socketFileDesc, & rcvSocketTimeout, 
    SO_RCVTIMEO);
  const int sndToutRetVal = getSocketTimeout(socketFileDesc, &sendSocketTimeout,
    SO_SNDTIMEO);
  
  if(rcvToutRetVal == -1){
    if(sndToutRetVal == -1)
      getSocketTimeoutRslt = getRcvAndSndTimeoutError;
    else
      getSocketTimeoutRslt = getRcvTimeoutError;
  }
  else
    if(sndToutRetVal == -1)
      getSocketTimeoutRslt = getSndTimeoutError;
  if(getSocketTimeoutRslt == success)
  {
    if(/** http://linux.die.net/man/7/socket :"If the timeout is set to zero
      * (the default) then the operation will never timeout."
      * <=>If not default timeout.
      * Linux Mint:If "tv_sec" and "tv_usec" = 0 then timeout after ca. 90 s.*/
      rcvSocketTimeout.tv_sec != 0 && rcvSocketTimeout.tv_usec != 0)
    {
      ///If *receive* timeout time < *send* timeout time.
      if(rcvSocketTimeout.tv_sec < sendSocketTimeout.tv_sec ||
         (rcvSocketTimeout.tv_sec == sendSocketTimeout.tv_sec &&
         rcvSocketTimeout.tv_usec < sendSocketTimeout.tv_usec)
        )
        /**=>receive timeout < send timeout */
        assign(p_timeoutInS, &rcvSocketTimeout);
      else
        /**<=>receive timeout >= send timeout if send timeout:
         * - <> 0 or
         * - == 0 AND receive timeout >= real send timeout (ca. 90 s)*/
        assign(p_timeoutInS, &sendSocketTimeout);
    }
    /** http://linux.die.net/man/7/socket :"If the timeout is set to zero
     * (the default) then the operation will never timeout."
     * <=>If default timeout.*/
    else
/**Send timeout <= receive timeout only if default receive timeout <> endless
 * and send timeout <= default receive timeout*/
      assign(p_timeoutInS, &sendSocketTimeout);
  }else if(getSocketTimeoutRslt == getRcvTimeoutError)
    assign(p_timeoutInS, &sendSocketTimeout);
  else if(getSocketTimeoutRslt == getSndTimeoutError)
    assign(p_timeoutInS, &rcvSocketTimeout);
  return getSocketTimeoutRslt;
}

TU_Bln361095BSDsktNmSpcEnd
