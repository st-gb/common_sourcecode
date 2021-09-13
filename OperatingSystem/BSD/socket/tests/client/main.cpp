#include "../../prepCnnctToSrv.h"///prepCnnctToSrv(...)
///BlockingCnnctError::GetPossibleCause_inl(...)
#include "../../blckngCnnctErrMsg.hpp"
#include <netinet/in.h>///struct sockaddr_in
#include <arpa/inet.h>///inet_ntoa(...)
#include "../../cxxopts/client/handleCmdLineArgs.hpp"

using namespace OperatingSystem::BSD::sockets;

int main(int argCount, char * args[])
{
  int port;
  std::string host = "localhost";
  client::HandleCmdLineOpts(argCount, args, port, host);

  struct sockaddr_in srvAddr;
  int socketFileDesc;
  PrepCnnctToSrvRslt prepCnnctToSrvRslt = prepCnnctToSrv(host.c_str(), port,
    &srvAddr, AF_INET, &socketFileDesc);
  if(prepCnnctToSrvRslt == prepCnnctToSrvSucceeded)
  {
    std::cout << "Connecting to " << inet_ntoa(srvAddr.sin_addr) << " port:" 
      << port << std::endl;
    const int retVal = connect(socketFileDesc,(struct sockaddr *) & srvAddr, 
      sizeof(srvAddr));
    if(retVal == -1)
    {
      int cnnctErrCode = errno;
      const enum errorCodes BSDsockErr = OperatingSystem::BSD::sockets::
        GetLastError();
      std::cout << "Connecting failed. Error code:" << cnnctErrCode <<std::endl;
      std::cout<< OperatingSystem::BSD::sockets::BlockingCnnctError::
        GetPossibleCause_inl(BSDsockErr, port);
    }
    else
      std::cout << "Successfully connected to server." << std::endl;
  }
  else
    std::cout << "Preparing connect to server failed. Error code:" << 
      prepCnnctToSrvRslt << std::endl;
  return 0;
}
