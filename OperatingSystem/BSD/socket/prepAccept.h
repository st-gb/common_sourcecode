/** File:   prepAccept.h
 * Author: sg
 * Created on 20. April 2020, 12:26 */

#ifndef PREPACCEPT_H
#define PREPACCEPT_H

#include "initSrv.h"

namespace OperatingSystem{ namespace BSD { namespace sockets{

enum InitSrvRslt prepAccept(
  const unsigned portNumber,
  struct sockaddr_in & srvAddr,
  const int protoFam,///e.g. AF_INET for IPv4
  const int maxCnnctns,
  int & socketFileDesc);

}}}

#endif /* PREPACCEPT_H */
