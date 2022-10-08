///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
#ifdef TU_Bln361095usePrgmInclGrd
  #pragma once
#endif
#if ! defined TU_Bln361095usePrgmInclGrd && \
  /**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrcBSDskt_errorCode_h
  #define TU_Bln361095cmnSrcBSDskt_errorCode_h

///TU_Bln361095OpSysUse(GetErrorMsg)
#include <OperatingSystem/ErrorCode/getErrorMsg.h>

#ifdef __cplusplus
  #define TU_Bln361095BSDsktGetErrorMsgNmSpc getErrorMsg
  #define TU_Bln361095BSDsktGetErrorMsgNmSpcBgn namespace \
    TU_Bln361095BSDsktGetErrorMsgNmSpc{
  #define TU_Bln361095BSDsktGetErrorMsgNmSpcEnd }
  #define TU_Bln361095BSDsktRsltTypeNmSpc rsltType
  #define TU_Bln361095BSDsktRsltTypeNmSpcBgn namespace \
    TU_Bln361095BSDsktRsltTypeNmSpc{
  #define TU_Bln361095BSDsktRsltTypeNmSpcEnd }
  #define TU_Bln361095BSDsktRsltTypeDef(suffix) TU_Bln361095BSDsktDef(suffix)
  #define TU_Bln361095BSDsktRsltTypeUse(suffix)\
   /*TU_Bln361095BSDsktUse(rsltType :: suffix)*/\
   TU_Bln361095BSDsktNmSpc rsltType :: suffix
  #define TU_Bln361095GetErrorMsgDef(suffix) TU_Bln361095BSDsktDef(suffix)
  #define TU_Bln361095GetErrorMsgUse(suffix) TU_Bln361095BSDsktNmSpc suffix
#else
  #define TU_Bln361095BSDsktGetErrorMsgNmSpc /**->empty*/
  #define TU_Bln361095BSDsktGetErrorMsgNmSpcBgn /**->empty*/
  #define TU_Bln361095BSDsktGetErrorMsgNmSpcEnd /**->empty*/
  #define TU_Bln361095BSDsktRsltTypeNmSpc /**->empty*/
  #define TU_Bln361095BSDsktRsltTypeNmSpcBgn /**->empty*/
  #define TU_Bln361095BSDsktRsltTypeNmSpcEnd /**->empty*/
  #define TU_Bln361095BSDsktRsltTypeDef(suffix)\
   TU_Bln361095BSDsktDef(RsltType##suffix)
  #define TU_Bln361095BSDsktRsltTypeUse(suffix)\
   TU_Bln361095BSDsktUse(RsltType##suffix)
  #define TU_Bln361095GetErrorMsgDef(suffix)\
   TU_Bln361095BSDsktDef(GetErrorMsg##suffix)
  #define TU_Bln361095GetErrorMsgUse(suffix)\
   TU_Bln361095BSDsktUse(GetErrorMsg##suffix)
#endif

#ifdef __linux__
  #include <OperatingSystem/POSIX/BSD_sockets/errorCode.h>
#endif

TU_Bln361095BSDsktNmSpcBgn

TU_Bln361095BSDsktRsltTypeNmSpcBgn
enum TU_Bln361095BSDsktDef(RsltType){
  ///Operating System-specific BSD skt error code:"errno" or WSAGetLastError()
  TU_Bln361095BSDsktRsltTypeDef(_errno),
/**Error code type of older BSD sockets function. For example see
 * http://en.wikipedia.org/wiki/Berkeley_sockets#gethostbyname_and_gethostbyaddr
 */
  TU_Bln361095BSDsktRsltTypeDef(_h_errno),
/**Newer Internet Procotol version 6-capable (POSIX) functions like
 * getnameinfo(...). Error codes of this type can be passed to function
 * "gai_strerror"(...) to get error messages for the code.*/
  TU_Bln361095BSDsktRsltTypeDef(IPv4or6fns),
///Error code specific to "TU_Bln361095BSDsktUse(GetHostName)" function.
  TU_Bln361095BSDsktRsltTypeDef(GetHostNm),
  TU_Bln361095BSDsktRsltTypeDef(GetIPaddrAsStr)
};
TU_Bln361095BSDsktRsltTypeNmSpcEnd

TU_Bln361095BSDsktGetErrorMsgNmSpcBgn
enum TU_Bln361095GetErrorMsgDef(Rslt){
  TU_Bln361095GetErrorMsgDef(Success) = 0,
  TU_Bln361095GetErrorMsgDef(/*ArrTooSmall*/InsuffBuf)
};
TU_Bln361095BSDsktGetErrorMsgNmSpcEnd

/**Force inlining to avoid multiple definitions of this function when linking->
 * compiler error.*/
/**@param rslt result value of/for type {@link rsltType}
 *   if {@link rsltType} = _errno then it should be WSAGetLastError() for MS Win
 * @param rsltType type of the result value, for example "h_errno" errors
 * @return (English) error message or NULL if @param rsltType is not supported*/
TU_Bln361095frcInln const char * TU_Bln361095BSDsktDef(GetErrorMsg)(
  const int rslt,
  const unsigned rsltType)
{
  switch((enum TU_Bln361095BSDsktRsltTypeUse(RsltType) ) rsltType){
    case TU_Bln361095BSDsktRsltTypeUse(_errno):///"errno" or WSAGetLastError())
    {
     char * errorMsg;
     int numBufChars;
     return /*TU_Bln361095BSDsktUse(GetErrorMsg)*/
/**The error message for MS Windows can be retrieved from WSAGetLastError(),
 *  , too by the use of the standard (FormatMessage(...) for getting the
 *  Operating System error message.*/
        TU_Bln361095OpSysUse(GetErrorMsg)(rslt, errorMsg, & numBufChars,
        TU_Bln361095OpSysUse(EnUS) );
    }
    case TU_Bln361095BSDsktRsltTypeUse(IPv4or6fns): return gai_strerror(rslt);
    case TU_Bln361095BSDsktRsltTypeUse(_h_errno): return hstrerror(rslt);
  }
  return NULL;
}

TU_Bln361095BSDsktNmSpcEnd

#endif///#ifndef TU_Bln361095cmnSrcBSDskt_errorCode_h
