#pragma once///Include guard

///Use inline to prevent multiple defintions of this function
inline int setBlockingSocket(const int socketFileDesc){
  ///Winsock:
  ///https://stackoverflow.com/questions/9534088/using-winsock-for-socket-programming-in-c
  ///https://docs.microsoft.com/de-de/windows/win32/api/winsock/nf-winsock-ioctlsocket?redirectedfrom=MSDN
  unsigned long off = 0;
  int rtrnVal = ioctlsocket(socketFileDesc, 
    /**https://www.ibm.com/support/knowledgecenter/SSB23S_1.1.0.2020/gtpc1/block.html :
     * "When FIONBIO is set, the socket is marked nonblocking." */FIONBIO, &off);
//  if(rtrnVal == 0)
  return rtrnVal;
}

///Use inline to prevent multiple defintions of this function
inline int setNonBlockingSocket(const int socketFileDesc){
  ///Winsock:
  ///https://stackoverflow.com/questions/9534088/using-winsock-for-socket-programming-in-c
  ///https://docs.microsoft.com/de-de/windows/win32/api/winsock/nf-winsock-ioctlsocket?redirectedfrom=MSDN
  unsigned long on = 1;
  int rtrnVal = ioctlsocket(socketFileDesc, 
    /**https://www.ibm.com/support/knowledgecenter/SSB23S_1.1.0.2020/gtpc1/block.html :
     * "When FIONBIO is set, the socket is marked nonblocking." */FIONBIO, &on);
  //if(rtrnVal == 0)
  return rtrnVal;
}