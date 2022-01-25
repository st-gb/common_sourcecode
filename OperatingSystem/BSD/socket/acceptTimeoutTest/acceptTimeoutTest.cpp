/** This program should test whether a setsocketopt(...) on client side can be
* used to set the  client connect() timeout. */
#include "../initSrv.h"///enum InitSrvRslt, getErrorMsg(...)
#include "../prepAccept.h"///prepAccept(...)
#include "../getSocketFileDesc.h"///getSocketFileDesc(...)
/**For isblank(int) to be in namespace "std" in file <c++/cctype> (at least
 * in MinGW). This is needed for cxxopts.hpp. <c++/cctype> is  indirectly 
 * included by <iostream> */
#define _GLIBCXX_USE_C99_CTYPE_TR1
#include <iostream>///std::cerr, std::cout
#include <netinet/in.h>///struct sockaddr_in
#include <arpa/inet.h>///inet_ntoa(...)

///Stefan Gebauer's "common_sourcecode" repository files:
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

namespace progError{
  enum progError{noError = 0, cmdLneArgsError, listenToSocketFailed};
}

int main(int cmdLneArgCnt, char * cmdLneArgs[])
{
  int retVal = progError::noError;
  std::string errorMsg;
  const int portNo = cxxopts::server::HandleCmdLineOpts(cmdLneArgCnt,
    cmdLneArgs,errorMsg);

  if(!errorMsg.empty() ){
    std::cerr << "Error processing command line arguments:" << errorMsg <<
      std::endl;
    return progError::cmdLneArgsError;
  }
  struct sockaddr_in srvAddr;
  int srvSocketFileDesc;
  enum InitSrvRslt initSrvRslt = OperatingSystem::BSD::sockets::prepAccept(
    portNo, srvAddr, 5, AF_INET, srvSocketFileDesc);
  if( initSrvRslt != listenSucceeded)
  {
    std::string errMsg = OperatingSystem::BSD::sockets::getErrorMsg(initSrvRslt);
    std::cerr << "ERROR with socket port:" << portNo << ":" << errMsg <<
      std::endl;
    retVal = progError::listenToSocketFailed;
  }
  else
    acceptLoop(portNo, srvSocketFileDesc);
  return retVal;
}
