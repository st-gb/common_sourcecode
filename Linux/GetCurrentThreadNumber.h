#pragma once

//#ifdef __linux__
//  #include <pthread.h> //pthread_self()
//#endif
#include <sys/types.h> //gettid();
#include <sys/syscall.h> //syscall(...)

namespace Linux
{
  inline //DWORD 
    unsigned GetCurrentThreadNumber() { return //::pthread_self(); 
    //http://linux.die.net/man/2/syscall
    ::syscall(SYS_gettid); }
}
