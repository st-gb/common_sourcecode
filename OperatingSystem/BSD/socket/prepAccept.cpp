#include "initSrv.h"///enum InitSrvRslt
/** https://pubs.opengroup.org/onlinepubs/009695399/functions/listen.html :
  * includes <sys/socket.h> */
#include <sys/socket.h>///listen(...)

namespace OperatingSystem{ namespace BSD { namespace sockets{
/** Name comes from the work done before calling "accept". Because accept(...)
* is specific to TCP and not needed for UDP.
* accept(...) is non-blocking by calling fcntl(...O_NONBLOCK) before.
* For steps needed see: https://en.wikipedia.org/wiki/Berkeley_sockets#Server */
enum InitSrvRslt prepAccept(
  const unsigned port,
  struct sockaddr_in & srvAddr,
  const int maxCnnctns,///For SOCK_STREAM/TCP
  ///http://man7.org/linux/man-pages/man2/socket.2.html : e.g. AF_INET for IPv4
  const int protoFam,
  int & socketFileDesc)
{
  enum InitSrvRslt retCode = initSrv(srvAddr,port,protoFam,
    /**http://man7.org/linux/man-pages/man2/socket.2.html : "Provides sequenced,
    * "reliable, two-way, connection-based byte streams."*/SOCK_STREAM/**TCP*/,
    socketFileDesc);
  if(retCode == boundToSocket)
  {
    /** https://linux.die.net/man/2/listen :
    * "listen() marks the socket referred to by sockfd as a passive socket,
    * that is, as a socket that will be used to accept incoming connection
    * requests using accept(2)." */
    /** https://linux.die.net/man/2/listen : 
     * "For "SOCK_STREAM" or "SOCK_SEQPACKET"*/
    if( listen(socketFileDesc, 
      /**http://man7.org/linux/man-pages/man2/listen.2.html :
        "The backlog argument defines the maximum length to which the queue of
       pending connections for sockfd may grow.  If a connection request
       arrives when the queue is full, the client may receive an error with
       an indication of ECONNREFUSED or, if the underlying protocol supports
       retransmission, the request may be ignored so that a later reattempt
       at connection succeeds." */maxCnnctns) == 0 )
      retCode = listenSucceeded;
    else 
      retCode = listenToSocketFailed;
  }
  return retCode;
}
}}}
