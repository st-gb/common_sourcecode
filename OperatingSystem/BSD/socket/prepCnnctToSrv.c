#include "sockaddr_in.h"///struct sockaddr_in

#include <strings.h>///bzero(...), bcopy(...)

#include "prepCnnctToSrv.h"///enum CnnctToSrvRslt
#include "getSocketFileDesc.h"///GetSocketFileDesc(...)
#include "getHostDBentry.h"///GetHostDataBaseEntry(...)

#ifdef __cplusplus
using namespace OperatingSystem::BSD::sockets;
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

/** Intension: should be usable by a minimal test program and other clients.
* It is separated from the connect to enable either an nonblocking 
* (via connect(...), select(...)" or a blocking connect (via "connect(...)" 
* Additionally so both connect() can be executed in another thread */
enum PrepCnnctToSrvRslt prepCnnctToSrv(
  const char hostName [],
  const int portNumber,
  struct sockaddr_in * p_srvAddr,
  const int protoFam,///AF_INIT for IPv4
  int * p_socketFileDesc)
{
  //from http://www.linuxhowtos.org/data/6/client.c
  struct hostent * p_serverHostDataBaseEntry;
  
  *p_socketFileDesc = GetSocketFileDesc(protoFam, SOCK_STREAM, 0);
  if(*p_socketFileDesc < 0)
    return getSocketFileDescFailed;
  
  p_serverHostDataBaseEntry = GetHostDataBaseEntry(hostName);
  if( ! p_serverHostDataBaseEntry )
    return getHostByNameFailed;

  memset( (char *) p_srvAddr, 0, sizeof(*p_srvAddr) );
  p_srvAddr->sin_family = protoFam;
  memcpy(
    (char *) & p_srvAddr->sin_addr.s_addr,
    (char *) p_serverHostDataBaseEntry->h_addr,
    p_serverHostDataBaseEntry->h_length);
  p_srvAddr->sin_port = htons(portNumber);
  return prepCnnctToSrvSucceeded;
}
#ifdef __cplusplus
}}}///end namespaces
#endif
