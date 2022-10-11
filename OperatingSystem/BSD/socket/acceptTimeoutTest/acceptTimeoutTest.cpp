/**(c)from 2020 Stefan Gebauer,Computer Science Master(TU Berlin matr. # 361095)
 * Created ca.20Apr2020 by Stefan Gebauer(TU Berlin matriculation number 361095)
 * This program should test whether a setsocketopt(...) on client side can be
 * used to set the client connect() timeout.
 * Must be compiled as C++ when it uses "cxxopts".*/

///Standard C(++) header files:
/**For function "isblank(int)" to be in namespace "std" in file <c++/cctype>
 * (at least in "MinGW" compiler suite). <c++/cctype> is indirectly included by
 * <iostream>. This is needed for <cxxopts.hpp> from Lightweight C++ command
 * line option parser.*/
#define _GLIBCXX_USE_C99_CTYPE_TR1
#include <iostream>///std::cerr, std::cout

///http://pubs.opengroup.org/onlinepubs/009695399/functions/shutdown.html
//#include <sys/socket.h>///shutdown(...)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint)
///cxxopts::server::HandleCmdLineOpts(...)
#include <OperatingSystem/BSD/socket/cxxopts/server/handleCmdLneOpts.hpp>
///accept(...), TU_Bln361095BSDsktDef(addrLenType)
#include <OperatingSystem/BSD/socket/accept_fn.h>
///TU_Bln361095BSDsktRsltTypeUse()
#include <OperatingSystem/BSD/socket/errorCode.h>
///TU_Bln361095BSDsktIPvUse(GetPort)(...)
#include <OperatingSystem/BSD/socket/getPort.h>
///TU_Bln361095BSDsktIPvUse(GetIPaddrAsStr)
#include <OperatingSystem/BSD/socket/getIPaddrAsStr.h>
/**enum TU_Bln361095BSDsktPrepAccptUse(Rslt),TU_Bln361095BSDsktPrepAccptUse(
 * GetEnErrorMsg)(...),TU_Bln361095BSDsktUse(PrepAccept)(...)*/
#include <OperatingSystem/BSD/socket/prepAccept.h>
///Needs to be included after/below all other IPv4/6 header files
///TU_Bln361095BSDsktIPvUse(SktAddrType)
#include <OperatingSystem/BSD/socket/sktAddrType.h>
///TU_Bln361095MicroSoftWindows
#include <OperatingSystem/Windows/MicrosoftWindows.h>

///OS-specific header files:
#ifdef TU_Bln361095MicroSoftWindows
  #include <conio.h>///kbhit()
#endif
#ifdef __linux__
  #include <signal.h>///signal(...)
  #include <unistd.h>///close(...)
#endif

static int s_srvSktFileDesc;
static int s_ctrlCpressed = 0;

void CtrlC_fn(int sigNr){
  printf(" Ctrl-C pressed\n");
  s_ctrlCpressed = 1;
  ///End "accept" loop by ending socket:
//  shutdown(s_srvSocketFileDesc);
  close(s_srvSktFileDesc);
}

inline int acceptLoop(const int portNo)
{
  int runLoop = 1;
  int atLeast1Clnt = 0;
  do
  {
//    struct sockaddr_in clntSktAddrIPv4;
    TU_Bln361095BSDsktIPvUse(SktAddrType) clntSktAddr;
/** http://long.ccaba.upc.edu/long/045Guidelines/eva/ipv6.html :
 *  "Portable source code:"*/
//    struct sockaddr_storage clntSktAddr;
    const int clntSktAddrSizeInB = sizeof(clntSktAddr);
    printf("\nWaiting for client connect on port %u\n", portNo);
    printf("Press Ctrl-C to end the program.\n");
    const int clntSktFileDesc = 
/** accept(...) is usually blocking (can be canceled with shutdown(...)/
 *   close(...) from another thread?):
 * http://pubs.opengroup.org/onlinepubs/009696699/functions/accept.html : "If
 *  the listen queue is empty of connection requests and O_NONBLOCK is not set
 *  on the file descriptor for the socket, accept() shall block until a
 *  connection is present."*/
     accept(
      s_srvSktFileDesc, 
      (struct sockaddr *) & clntSktAddr,
      (TU_Bln361095BSDsktUse(addrLenType))& clntSktAddrSizeInB);
    if(clntSktFileDesc == -1){
      runLoop = 0;
      if(s_ctrlCpressed)
        printf("Ctrl-C pressed");
      else
        printf("Error on waiting for client connects");
      printf("->ending client connect loop.\n");
      break;
    }
    atLeast1Clnt = 1;
    const int clntSktPrt = TU_Bln361095BSDsktIPvUse(GetPort)(clntSktAddr);
    char IPaddrStr [100] = "";
    char * p_IPaddrStr = IPaddrStr;
    TU_Bln361095BSDsktRsltTypeUse(RsltType) rslt;
    if(TU_Bln361095BSDsktIPvUse(GetIPaddrAsStr)(&clntSktAddr, &p_IPaddrStr, 99,
      &rslt) == TU_Bln361095BSDsktGetIPaddrAsStrUse(Success) )
      printf("Client connected: port:%u IP addr:%s\n", clntSktPrt,p_IPaddrStr);
    #ifdef TU_Bln361095MicroSoftWindows
      runLoop = !kbhit();
    #endif
  }while(runLoop);
  return atLeast1Clnt;
}

#define progExit(suffix) progExit##suffix
//namespace progExit{
enum progExitCodes{
  progExit(Success) = 0,
  progExit(CmdLneOptsError),
  progExit(ByndLast) = progExit(CmdLneOptsError) + 
    TU_Bln361095BSDsktPrepAccptUse(listenToSktFailed) + 1};

const char * const enExitCodeStr[]{
  "success (waited for client connects)",
  "command line options (parse/processing) error",
};

void outputProgExitCodes()
{
  int progExitCode = 0;
  printf("Program exit codes:\n");
  for(TU_Bln361095CPUuse(FaststUint) idx = 0;idx <= progExit(CmdLneOptsError);
    idx++, progExitCode++)
    printf("%u:%s\n", progExitCode, enExitCodeStr[idx]);
  for(TU_Bln361095CPUuse(FaststUint) idx = 0; idx <=
    TU_Bln361095BSDsktInitSrvUse(failedToBindToSkt);idx++, progExitCode++)
    printf("%u:%s\n", progExitCode, TU_Bln361095BSDsktInitSrvUse(EnErrorMsgs)[
      idx] );
}

int main(int cmdLneArgCnt, char * cmdLneArgs[])
{
  int exitCode = progExit(Success);
  std::string errorMsg;
  if(cmdLneArgCnt == 1)
    outputProgExitCodes();
  const int portNo = cxxopts::server::HandleCmdLineOpts(cmdLneArgCnt,
    cmdLneArgs,errorMsg);

  if(!errorMsg.empty() ){
    std::cerr << "Error processing command line arguments:" << errorMsg <<
      std::endl;
    return progExit(CmdLneOptsError);
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
    exitCode = progError::listenToSocketFailed;
  }
  else{
    signal(SIGINT,CtrlC_fn);
    int rslt = acceptLoop(portNo);
  }
  return exitCode;
}
