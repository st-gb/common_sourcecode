/** File:   connToSrv.h
 * Author: sg
 * Created on 5. April 2020, 02:02 */
#pragma once///Include guard
#ifndef PREPCNNCTOSRV_H
#define PREPCNNCTOSRV_H

///Forward declaration
struct sockaddr_in;

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
/**Ensures no C++ function name mangling.-> function _definition_ compiled with 
 * C compiler (non-mangled name) usable in C++ code.*/
extern "C"{
#endif

enum PrepCnnctToSrvRslt{prepCnnctToSrvSucceeded = 0, 
  getSocketFileDescFailed,///calling connect() returned -1
  getHostByNameFailed///gethostbyname(...) returned NULL
  };

enum PrepCnnctToSrvRslt prepCnnctToSrv(
  const char host [],///e.g."localhost"
  const int portNumber,
  struct sockaddr_in * p_srvAddr,
  const int protoFam,///e.g. AF_INIT for IPv4
  int * p_socketFileDesc);

#ifdef __cplusplus
}///end extern "C"
}}}///end namespace
#endif

#endif /* PREPCNNCTOSRV_H */
