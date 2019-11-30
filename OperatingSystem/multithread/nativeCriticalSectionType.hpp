#ifndef NATIVE_CRITICAL_SECTION_TYPE_HPP_
#define NATIVE_CRITICAL_SECTION_TYPE_HPP_

#ifdef _WIN32 /** pre-defined macro, also for 64 bit Windows */
  #include <OperatingSystem/Windows/multithread/CriticalSection.hpp>
  typedef OperatingSystem::Windows::CriticalSection nativeCriticalSection_type;
#endif

#ifdef __linux__ //TODO: change to ifdef POSIX
  #include <OperatingSystem/POSIX/multithread/pthread_Based_I_CriticalSection.hpp>
  typedef pthread_Based_I_CriticalSection nativeCriticalSection_type;
#endif

#endif /* NATIVE_CRITICAL_SECTION_TYPE_HPP_ */
