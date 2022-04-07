#include "../../prepCnnctToSrv.h"///prepCnnctToSrv(...)
///BlockingCnnctError::GetPossibleCause_inl(...)
#include "../../blckngCnnctErrMsg.hpp"
#include <netinet/in.h>///struct sockaddr_in
#include <arpa/inet.h>///inet_ntoa(...)
///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
#include "../../cxxopts/client/handleCmdLineArgs.hpp"

/**Use C functions like "printf" to enable both C and C++ builds.*/

using namespace OperatingSystem::BSD::sockets;
/**Name it "progError" because the most values are errors? So the value names
 * can be shorter? Or name it "exitCode" because so it is clear that it is a
 * return code?*/
#define progExitCode(suffix) progExitCode##suffix

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
  /**Enclose in double ticks (") because the address string may be something
   * like "::" (IPv6 address).*/
  printf("Connecting to IP address:\"%s\"", srvAddrStr);
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
