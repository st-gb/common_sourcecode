/*
 * nativeCriticalSectionType.hpp
 *
 *  Created on: 08.04.2011
 *      Author: sgebauer
 */

#ifndef NATIVE_THREAD_TYPE_HPP_
#define NATIVE_THREAD_TYPE_HPP_

#ifdef _WIN32 //pre-defined macro, also for 64 bit Windows
	#include <OperatingSystem/Windows/multithread/Thread.hpp>
	typedef Windows_API::Thread nativeThread_type;
#endif

#ifdef __linux__ //TODO change to #ifdef POSIX
  #include <OperatingSystem/POSIX/multithread/pthreadBasedI_Thread.hpp>
  typedef POSIX::pthreadBasedI_Thread nativeThread_type;
#endif

#endif /* NATIVE_THREAD_TYPE_HPP_ */
