#pragma once
//#include <netinet/in.h>///struct sockaddr_in
#include <string>///class std::string

///Forward declaration.
struct sockaddr_in;
//namespace std{class string;}

namespace OperatingSystem{ namespace BSD { namespace sockets{

enum InitSrvRslt {listenSucceeded = 0, boundToSocket = 0, createSocketFailed,
  failedToBindToSocket, listenToSocketFailed};

///Can be used for TCP and UDP.
enum InitSrvRslt initSrv(
  struct sockaddr_in & srvAddr,
  const int port,
  const int protoFam,///e.g. AF_INIT for IPv4
  const int type,///e.g. SOCK_STREAM for TCP
  int & socketFileDesc);

std::string getErrorMsg(enum InitSrvRslt &);
}}}///end namespaces
