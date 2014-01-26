#pragma once

//#ifdef __linux__
//  #include <pthread.h> //pthread_self()
//#endif

/** from http://stackoverflow.com/questions/6374523/how-to-detect-compilation-by-android-ndk-in-a-c-c-file */
#ifdef __ANDROID__
	#define LINUX_GET_CURRENT_THREAD_NUMBER_DUMMY_IMPLEMENTATION
	//from https://groups.google.com/forum/#!topic/android-ndk/808Ti2v1I0s
	#include <unistd.h>
#endif
#if !defined(LINUX_GET_CURRENT_THREAD_NUMBER_DUMMY_IMPLEMENTATION)
	#include <sys/types.h> //gettid();
	/** http://manpages.courier-mta.org/htmlman2/syscall.2.html */
	#include <sys/syscall.h> //syscall(...) /* For SYS_xxx definitions */
#endif

namespace Linux
{
  inline //DWORD 
    unsigned GetCurrentThreadNumber() { return //::pthread_self(); 
#ifdef LINUX_GET_CURRENT_THREAD_NUMBER_DUMMY_IMPLEMENTATION
	/** "SYS_gettid" not defined in Android NDK */
	  //0;
    pthread_self();
#else
	  /** http://linux.die.net/man/2/syscall */
	  ::syscall(SYS_gettid);
#endif
  }
}
