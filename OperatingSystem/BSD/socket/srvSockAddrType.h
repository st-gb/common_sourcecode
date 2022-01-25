#pragma once///Include guard

#include <compiler/force_inline.h>///force_inline

/** "TU_Berlin361095_IPv" instead of for example "IPv" to avoid name conflicts
 *  with definitions from other included files.
 *  Define as compiler definition.*/
#if TU_Berlin361095_IPv == 4
  ///Forward declaration
  struct sockaddr_in;
  
  typedef struct sockaddr_in srvSockAddrType;
  typedef srvSockAddrType * srvSockAddrPtrType;
  force_inline void FreeBSDsockAddr(const struct sockaddr_in sockAddr){
    /**Empty function definition--correct?*/}
#else
  /**"struct addrinfo" is available in MinGW's "ws2tcip.h" independent of
   * _WIN32_WINNT.*/
  typedef struct addrinfo * srvSockAddrType;
  typedef srvSockAddrType * srvSockAddrPtrType;
  force_inline void FreeBSDsockAddr(struct addrinfo * const p_addrInfo){
    /**"freeaddrinfo" is only available if _WIN32_WINNT >= 0x0501 in <ws2tcip.h>:
     *  -in TDM-GCC (for example version 9.2) 32 bit
     *  -MinGW (for example version 5.3.0-2) 32 bit
     * "freeaddrinfo" is available in "ws2tcip.h" of (recent) MinGW w64
     * independent of "_WIN32_WINNT"/in any case.*/
    freeaddrinfo(p_addrInfo); }
#endif
