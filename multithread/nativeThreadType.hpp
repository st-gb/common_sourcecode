/*
 * nativeCriticalSectionType.hpp
 *
 *  Created on: 08.04.2011
 *      Author: sgebauer
 */

#ifndef NATIVE_THREAD_TYPE_HPP_
#define NATIVE_THREAD_TYPE_HPP_

#ifdef _WIN32 //pre-defined macro, also for 64 bit Windows
	#include <Windows/multithread/Thread.hpp>
	typedef Windows_API::Thread nativeThread_type;
#endif

#ifdef __linux__
//  #include <wxWidgets/multithread/wxCriticalSectionBasedI_CriticalSection.hpp>
//  typedef wxCriticalSectionBasedI_CriticalSection nativeCriticalSection;
//  typedef wxCriticalSectionBasedI_CriticalSection CriticalSection_type;

  #include <Linux/multithread/pthread_Based_I_Thread.hpp>
  typedef pthread_Based_I_CriticalSection nativeCriticalSection;
  typedef pthread_Based_I_CriticalSection nativeThread_type;

#endif

#endif /* NATIVE_THREAD_TYPE_HPP_ */
