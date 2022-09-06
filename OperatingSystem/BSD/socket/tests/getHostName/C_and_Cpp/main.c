///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matric.#361095)

///Standard C header files:
#include <stdio.h>///printf(...)
#include <stdlib.h>///malloc(...)

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095BSDsktUse(GetBinIPaddr)(...)
#include <OperatingSystem/BSD/socket/getBinIPaddr.h>
///TU_Bln361095BSDsktUse(GetHostName)(...)
#include <OperatingSystem/BSD/socket/getHostName.h>
/**TU_Bln361095BSDsktIPvUse(SktAddrType):Must be below the socket functions if
 * IPv type is "auto" */
#include <OperatingSystem/BSD/socket/srvSockAddrType.h>
///TU_Bln361095OpSysUse(GetErrorMsg),TU_Bln361095OpSysGetErrorMsgUse(InsuffBuf)
#include <OperatingSystem/ErrorCode/getErrorMsg.h>

///@return free pointer after use via free(...)
char * getErrorMsg(const int OSerrorCode, enum TU_Bln361095OpSysUse(Lang) lang)
{
  char * errorStr = NULL;
  TU_Bln361095OpSysGetErrorMsgUse(RtrnType) getErrorMsgRslt =
    TU_Bln361095OpSysUse(GetErrorMsg)(OSerrorCode, errorStr, 0, lang);
  return /*errorStr*/getErrorMsgRslt;
}

TU_Bln361095frcInl char * getEnErrorMsg(const int OSerrorCode)
{
  return getErrorMsg(OSerrorCode, TU_Bln361095OpSysUse(EnUS) );
}

///@param hostAddr IP address as character string
void getIPaddrAndGetHostName(
  const char hostAddr[])
{
  char arHostName[NI_MAXHOST +1];
  char * p_hostName = arHostName;
  ///Binary representation of IP address. E.g. IPv4 as 32 bit number
  TU_Bln361095BSDsktIPvUse(SktAddrType) sktAddr;
  TU_Bln361095CPUuse(FaststUint) rsltType;
  int rslt = TU_Bln361095BSDsktIPvUse(GetBinIPaddr)(
    hostAddr,
    0,///portNumber
    & sktAddr,
    & rsltType
    );
  printf("Result of GetBinIPaddr for \"%s\":%d\n",hostAddr,rslt);
  if(rslt == TU_Bln361095BSDsktGetBinIPaddrUse(Success) )
  {
    rslt/*p_hostName*/ = TU_Bln361095BSDsktIPvUse(
      GetHostName)(&sktAddr,/*NULL*/& p_hostName,/*0*/NI_MAXHOST, &rsltType);
    printf("Result of getHostName:%d\n", rslt);
      //p_hostName >(/**EAI_IDN_ENCODE*-1*/105) ? 0 : (int)p_hostName);
    if(/*p_hostName >= 106*/ rslt == 0)
      printf("(Resolved) host mame:\"%s\"\n", p_hostName);
    else{
     const char * errorStr = TU_Bln361095BSDsktUse(GetErrorMsg)(rslt, rsltType);
     if(errorStr){
       printf("Calling \"GetHostName\" failed:%s\n", errorStr);
     }
   }
//    free(p_hostName);
  }
  else{
    const char * errorStr = TU_Bln361095BSDsktUse(GetErrorMsg)(rslt, rsltType);
    if(errorStr){
      printf("Calling GetBinIPaddr failed:%s\n", errorStr);
//      free(errorStr);
    }
  }
}

enum progExitCodes{success=0,BSDsktInitError};

int main()
{
  int rslt = TU_Bln361095BSDsktUse(Bgn)();
  if(rslt != 0){
    char * enErrorStr = getEnErrorMsg(rslt);
    if(enErrorStr){
      printf("Initializing BSD sockets failed:%s\n", enErrorStr);
      free(enErrorStr);
    }
    return BSDsktInitError;
  }
#ifdef TU_Bln361095IPv4
  printf("Using Internet Protocol version 4 functions\n");
#else
  printf("Using Internet Protocol version 4 or 6 functions\n");
#endif
  getIPaddrAndGetHostName("127.0.0.1");
  getIPaddrAndGetHostName("::1");
  getIPaddrAndGetHostName(":::0");
  getIPaddrAndGetHostName("192.168.0.253");
  TU_Bln361095BSDsktUse(End)();
  return success;
}
