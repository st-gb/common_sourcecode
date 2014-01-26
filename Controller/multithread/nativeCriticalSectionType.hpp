/*
 * nativeCriticalSectionType.hpp
 *
 *  Created on: 08.04.2011
 *      Author: sgebauer
 */

#ifndef NATIVECRITICALSECTIONTYPE_HPP_
#define NATIVECRITICALSECTIONTYPE_HPP_

#ifdef _WIN32 //pre-defined macro, also for 64 bit Windows
  #include <Windows/multithread/CriticalSection.hpp>
  typedef OperatingSystem::Windows::CriticalSection nativeCriticalSection_type;
#endif

#ifdef __linux__
//  #include <wxWidgets/multithread/wxCriticalSectionBasedI_CriticalSection.hpp>
//  typedef wxCriticalSectionBasedI_CriticalSection nativeCriticalSection;
//  typedef wxCriticalSectionBasedI_CriticalSection CriticalSection_type;

  #include <Linux/multithread/pthread_Based_I_CriticalSection.hpp>
  typedef pthread_Based_I_CriticalSection nativeCriticalSection_type;
  typedef pthread_Based_I_CriticalSection CriticalSection_type;

#endif

#endif /* NATIVECRITICALSECTIONTYPE_HPP_ */
