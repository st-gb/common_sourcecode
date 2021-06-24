#pragma once ///Include guard

inline int getSocketError(const int socketFileDescriptor)
{
  /** http://man7.org/linux/man-pages/man2/connect.2.html :
   *  section "ERRORS" , "EINPROGRESS" :
   * "After select(2) indicates writability, use getsockopt(2) to read the
   *  SO_ERROR option at level SOL_SOCKET to determine whether
   *  connect() completed successfully (SO_ERROR is zero)" */
#ifdef __linux__
  /** http://pubs.opengroup.org/onlinepubs/7908799/xns/getsockopt.html
   * "This option stores an int value." */
  int iSO_ERROR;
  socklen_t optlen = sizeof(int);
  /** http://man7.org/linux/man-pages/man2/setsockopt.2.html
   * " On success, zero is returned for the standard options." */
  /// optval for SO_RCVBUF size is 16 if was connected
  /*result =*/ int getsockoptRslt = getsockopt(
    socketFileDescriptor,
    SOL_SOCKET /*int level*/,
    ///"This option stores an int value in the optval argument. "
    /** https://pubs.opengroup.org/onlinepubs/007908799/xns/getsockopt.html
     * SO_ERROR : "Reports information about error status and clears it.
     * This option stores an int value." */
    /*SO_RCVBUF,*/ SO_ERROR, //int optname
    & iSO_ERROR///POSIX: void *optval Windows Socket API: char * optval
    , & optlen //socklen_t *optlen
    );
  return iSO_ERROR;
#else
  return -1;
#endif
}

