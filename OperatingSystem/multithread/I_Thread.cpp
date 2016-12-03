/*
 * I_Thread.cpp
 *
 *  Created on: 10.02.2013
 *      Author: Stefan
 */
#include <OperatingSystem/multithread/I_Thread.hpp>
#include <OperatingSystem/multithread/GetCurrentThreadNumber.hpp>

//static var definitition:
I_Thread::threadNameMapType I_Thread::s_threadNumber2Name;
I_Thread::cs_type I_Thread::s_critical_section_type;

//const std::string * const I_Thread::GetThreadName(unsigned threadID)
//{
//}

void I_Thread::SetCurrentThreadName(const char * const name)
{
  DWORD currentThreadNumber = OperatingSystem::GetCurrentThreadNumber();
  //Enter the critical section to guard against concurrent changing or reading 
  //from the thread name container.
  s_critical_section_type.Enter();
    s_threadNumber2Name.insert( std::make_pair(currentThreadNumber,
    std::string(name)) );
  s_critical_section_type.Leave();
}

void I_Thread::SetThreadName(const char * const name, unsigned thread_ID)
{
  //Enter the critical section to guard against concurrent changing or reading 
  //from the thread name container.
  s_critical_section_type.Enter();
    s_threadNumber2Name.insert( std::make_pair(thread_ID,
    std::string(name)) );
  s_critical_section_type.Leave();
}

BYTE I_Thread::start(
  pfnThreadFunc pfnthreadfunc,
  void * p_v,
  const char * const threadName,
  /*BYTE*/ enum priority prio //= default_priority
  )
{
  BYTE t_start = start(pfnthreadfunc, p_v, prio);
  if( t_start == I_Thread::no_error)
  {
    unsigned threadID = GetThreadID();
    SetThreadName(threadName, threadID);
  }
  return t_start;
}

BYTE I_Thread::start(
  pfnThreadFunc pfnthreadfunc,
  void * p_v,
  /*BYTE*/ enum priority prio,
  const char * const threadName)
{
  BYTE t_start = start(pfnthreadfunc, p_v, prio);
  if(t_start == I_Thread::no_error)
    SetThreadName(threadName, GetThreadID() );
  return t_start;
}
