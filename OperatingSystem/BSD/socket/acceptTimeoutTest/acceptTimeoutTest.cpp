/** This program should test whether a setsocketopt(...) on client side can be
* used to set the  client connect() timeout. */
#include "../initSrv.h"///enum InitSrvRslt, getErrorMsg(...)
#include "../prepAccept.h"///prepAccept(...)
#include "../getSocketFileDesc.h"///getSocketFileDesc(...)
#include <iostream>///std::cerr, std::cout
#include <netinet/in.h>///struct sockaddr_in
#include <arpa/inet.h>///inet_ntoa(...)
#include "../cxxopts/handleCmdLineOpts.hpp"///HandleCmdLineOpts(...)

//void setPortNo(const char [] val){  }
//CommandLineOption<funcType> cmdLineOpts [] = {"port" , setPortNo};
//CmdLineOpt

using namespace OperatingSystem::BSD::sockets;///InitSrvRslt,prepAccept(...)

inline void acceptLoop(const int portNo, const int srvSocketFileDesc)
{
  do
  {
    struct sockaddr_in clientAddr;
    socklen_t sizeOfClientAddrInB = sizeof(clientAddr);
    std::cout << "Accepting on port " << portNo << "\n";
    ///accept(...) is blocking, can be cancelled with "shutdown(...)" (from
    ///another thread)
    const int clientSocketFileDesc = accept(
      srvSocketFileDesc, 
      (struct sockaddr *) & clientAddr, 
      & sizeOfClientAddrInB);
    std::cout << "Client connected: port:" << clientAddr.sin_port << 
      " IP addr:" << inet_ntoa(clientAddr.sin_addr) << std::endl;
  }while(1);
}

int main(int argCount, char * args[])
{
  int retVal = 0;
  const int portNo = cxxopts::clientAndServer::HandleCmdLineOpts(argCount,args);

  struct sockaddr_in srvAddr;
  int srvSocketFileDesc;
  enum InitSrvRslt initSrvRslt = OperatingSystem::BSD::sockets::prepAccept(
    portNo, srvAddr, 5, AF_INET, srvSocketFileDesc);
  if( initSrvRslt != listenSucceeded)
  {
    std::string errMsg = OperatingSystem::BSD::sockets::getErrorMsg(initSrvRslt);
    std::cerr << "ERROR with socket port:" << portNo << ":" << errMsg <<
      std::endl;
    retVal = 1;
  }
  else
    acceptLoop(portNo, srvSocketFileDesc);
  return retVal;
}
