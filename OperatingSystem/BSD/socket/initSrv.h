///(c)from 2020:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
  /**Non-standard include guard:supported by many, but not all industry compilers:
   * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
  /**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcBSDsktInitSrv_h
  #define TU_Bln361095cmnSrcBSDsktInitSrv_h

///Standard C(++) header files:
#include <stdio.h>///snprintf(...)
#include <string.h>///strncat(...)

///Stefan Gebauer's(TU Berlin mat.#361095) "common_sourcecode" repository files:
///TU_Bln361095BSDsktDef,TU_BlnBSDsktNmSpcBgn,TU_BlnBSDsktNmSpcEnd
#include "socket.h"
#include "errorCode.h"///TU_Bln361095BSDsktErrorCodeUse

///Forward declaration (faster than to #include files)
struct sockaddr_in;

#ifdef __cplusplus
  #define TU_Bln361095BSDsktInitSrvDef(suffix) TU_Bln361095BSDsktDef(suffix)
  #define TU_Bln361095BSDsktInitSrvUse(suffix) TU_Bln361095BSDsktUse(initSrv ::\
    suffix)
  #define TU_Bln361095BSDsktInitSrvNmSpcBgn namespace initSrv {
  #define TU_Bln361095BSDsktInitSrvNmSpcEnd }
#else
  #define TU_Bln361095BSDsktInitSrvDef(suffix) \
    TU_Bln361095BSDsktDef(InitSrv##suffix)
  #define TU_Bln361095BSDsktInitSrvUse(suffix) \
    TU_Bln361095BSDsktUse(InitSrv##suffix)
  #define TU_Bln361095BSDsktInitSrvNmSpcBgn
  #define TU_Bln361095BSDsktInitSrvNmSpcEnd
#endif

TU_Bln361095BSDsktNmSpcBgn

TU_Bln361095BSDsktInitSrvNmSpcBgn

/**Result of initializing BSD sockets server. Can be used for TCP and UDP.
 * "Init"=Initialize:http://www.abbreviations.com/abbreviation/Initialize 
 * "Srv"=server:http://www.abbreviations.com/abbreviation/server
 * "Rslt"=result:http://www.allacronyms.com/result/abbreviated*/
enum TU_Bln361095BSDsktInitSrvDef(Rslt){
//  TU_Bln361095BSDsktInitSrvDef(listenSucceeded) = 0,
  TU_Bln361095BSDsktInitSrvDef(boundToSkt) = 0,
  TU_Bln361095BSDsktInitSrvDef(createSktFailed),
  TU_Bln361095BSDsktInitSrvDef(failedToBindToSkt),
//  TU_Bln361095BSDsktInitSrvDef(listenToSktFailed)
  };

///Variables declared/defined in a source file:
extern const char * const EnErrorMsgs[];
extern const char * const BindToSktPossCauseEn;

/**@brief English error message for initializing BSD sockets server.
 * "En"=English
 * "Msg"=message:http://www.abbreviations.com/abbreviation/message
 * @param errorCode "errno" under POSIX/Linux or WSAGetLastError() under
 *  MicroSoft Windows
 * @param p_arErrorMsg pointer to/address of a character string array.
 *  the character string is stored in the dereferenced version of this
 *  variable
 *  -using a stack array:
 *   char buffer[10];
 *   char * p_buffer = buffer;
 *   Use "& p_buffer" for this parameter.
 *   The pointer has to be created because if using "& buffer": "& buffer" =
 *   buffer and if dereferencing, then the 1st character of the array would be
 *   used as address->program crash.
 *  -using a heap array:
 *   char * buffer = (char *) malloc(10);
 *   Use "& buffer" for this parameter.*/
TU_Bln361095frcInln void TU_Bln361095BSDsktInitSrvDef(GetEnErrorMsg)(
  enum TU_Bln361095BSDsktInitSrvUse(Rslt) initSrvRslt,
  const int errorCode,
  char ** p_arErrorMsg,
  unsigned numErrorMsgChars
  )
{
  const int numBprinted = snprintf(*p_arErrorMsg, numErrorMsgChars,
    "%s:%s(OS error #%u)\n",
    TU_Bln361095BSDsktInitSrvUse(EnErrorMsgs)[initSrvRslt],
    TU_Bln361095BSDsktUse(GetErrorMsg)(initSrvRslt, errorCode), errorCode);
  
  if(TU_Bln361095BSDsktUse(UnifyErrorCode)(errorCode) ==
     TU_Bln361095BSDsktErrorCodeUse(Access) )
  {
    if( initSrvRslt == TU_Bln361095BSDsktInitSrvUse(failedToBindToSkt) )
      strncat(*p_arErrorMsg,///dest
        TU_Bln361095BSDsktInitSrvUse(BindToSktPossCauseEn),///source
        numErrorMsgChars - numBprinted);
  }
}

TU_Bln361095BSDsktInitSrvNmSpcEnd

/**@brief Initializes BSD sockets server. Can be used for TCP and UDP.
 *  "Init"=Initialize:http://www.abbreviations.com/abbreviation/Initialize 
 *  "Srv"=server:http://www.abbreviations.com/abbreviation/server
 * @param port to listen to */
enum TU_Bln361095BSDsktInitSrvUse(Rslt)
  TU_Bln361095BSDsktDef(InitSrv)(
  struct sockaddr_in & srvAddr,
  const int port,
  const int protoFam,///e.g. AF_INIT for IPv4
  const int socketType,///e.g. SOCK_STREAM for TCP
  int * socketFileDesc,
  int * p_errorCode);

TU_Bln361095BSDsktNmSpcEnd

#endif///! defined TU_Bln361095cmnSrcBSDsktInitSrv_h