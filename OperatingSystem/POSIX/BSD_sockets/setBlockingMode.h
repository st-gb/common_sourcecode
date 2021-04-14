#pragma once

inline void setNonBlockingSocket(const int socketFileDescriptor){
  ///see https://www.cs.odu.edu/~cs779/spring10/lectures/nonblockingIO.html
  int flags = fcntl(socketFileDescriptor, F_GETFL, 0);
  fcntl(socketFileDescriptor, F_SETFL, flags | O_NONBLOCK);
}

inline void setBlockingSocket(const int socketFileDescriptor){
  ///see https://www.cs.odu.edu/~cs779/spring10/lectures/nonblockingIO.html
  int flags = fcntl(socketFileDescriptor, F_GETFL, 0);
  fcntl(socketFileDescriptor, F_SETFL, flags &
    /** "~": invert every bit */(~ O_NONBLOCK) );
}