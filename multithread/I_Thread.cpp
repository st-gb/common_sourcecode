/*
 * I_Thread.cpp
 *
 *  Created on: 10.02.2013
 *      Author: Stefan
 */
#include <Controller/multithread/I_Thread.hpp>
#include <Controller/multithread/GetCurrentThreadNumber.hpp>

//static var definitition:
I_Thread::threadNameMapType I_Thread::s_threadNumber2Name;

void I_Thread::SetCurrentThreadName(const char * const name)
{
  DWORD currentThreadNumber = OperatingSystem::GetCurrentThreadNumber();
  s_threadNumber2Name.insert( std::make_pair(currentThreadNumber,
    std::string(name)) );
}


