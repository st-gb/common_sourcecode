#pragma once///Include guard

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

inline void InitSocket(){///Without initializing a WSA error occurred
///https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
  /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
  wVersionRequested = MAKEWORD(2, 2);
  err = WSAStartup(wVersionRequested, &wsaData);
}

#if __cplusplus
}}}///namespaces ends
#endif