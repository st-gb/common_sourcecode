///Make C++ file in order to use reference operator ("&")
///For BSD sockets: https://en.wikipedia.org/wiki/Berkeley_sockets
#include "getSocketFileDesc.h"///GetSocketFileDesc(...)
#include "initSrv.h"///enum PrepAcceptRslt
#include <string.h>///memset(...)
#include <sys/socket.h>///bind(...)
#include <netinet/in.h>///struct sockaddr_in, htons(...), INADDR_ANY
#include <sstream>///std::ostringstream

using namespace OperatingSystem::BSD::sockets;

namespace OperatingSystem{ namespace BSD { namespace sockets
{
///Can be used for TCP and UDP.
enum InitSrvRslt initSrv(
  struct sockaddr_in & srvAddr,
  const int port,
  const int protoFam,///e.g. AF_INIT for IPv4
  const int type,///e.g. SOCK_STREAM for TCP
  int & socketFileDesc)
{
  enum InitSrvRslt retCode;
  //Code adapted from http://www.linuxhowtos.org/data/6/server.c
  memset(&srvAddr, 0, sizeof(srvAddr)); /* Clear structure */

  srvAddr.sin_family = protoFam;//AF_INET/**IPv4 Internet protocols*/;
  srvAddr.sin_addr.s_addr = INADDR_ANY;///Accept any incoming messages
  srvAddr.sin_port = htons(port);

  socketFileDesc = GetSocketFileDesc(
    protoFam,
    type,
    0/**protocol*/);

  if(socketFileDesc == -1)
    retCode = createSocketFailed;
  else{
  /** see/from 
  * http://stackoverflow.com/questions/10619952/how-to-completely-destroy-a-socket-connection-in-c
  *  : Avoid bind problems (errno = EADDRINUSE) */
//  int true_ = 1;
  /** https://linux.die.net/man/2/setsockopt :
   * "On error, -1 is returned, and errno is set appropriately." */ 
//  setsockopt(socketFileDesc, SOL_SOCKET, SO_REUSEADDR, & true_,sizeof(true_));
//  errno = 0;///setsockopt(...) error should not matter/influence.

  /** http://man7.org/linux/man-pages/man2/bind.2.html :
  * "bind() assigns the address specified by addr to the socket referred to by
  *  the file descriptor sockfd."
  * "On error, -1 is returned, and errno is set appropriately." */
  if(bind(socketFileDesc, (struct sockaddr *) & srvAddr, sizeof(srvAddr) ) < 0)
    retCode = failedToBindToSocket;
  else
    retCode = boundToSocket;
  return retCode;
  }
}

std::string getErrorMsg(enum InitSrvRslt & initSrvRslt)
{
  std::ostringstream oss;
  std::string engErrMsg = "failed to ";
  switch(initSrvRslt)
  {
   case createSocketFailed:
    engErrMsg += "create socket file descr.:"; break;
   case failedToBindToSocket:
    engErrMsg += "bind to socket:"; break;
   case listenToSocketFailed:
    engErrMsg += "listen to socket:"; break;
  }
  ///https://en.cppreference.com/w/cpp/locale/setlocale
//    char * p = std::setlocale(LC_MESSAGES/*LC_ALL*/, "de_DE.UTF-8");
  oss << engErrMsg << 
    /** https://linux.die.net/man/3/strerror :
    * "possibly using the LC_MESSAGES part of the current locale to select 
    * the appropriate language." */
    strerror(errno) << "(OS error #" << errno << ")\n";
  if(errno == EACCES)
  {
    if( initSrvRslt == failedToBindToSocket)
      oss << "Maybe because trying to bind to a well-known (1-1023) port\n";
    oss << "Maybe start this program as root/admin to fix.\n";
  }
  return oss.str();
}
}}}
