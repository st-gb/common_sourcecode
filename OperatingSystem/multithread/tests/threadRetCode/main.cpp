#include <OperatingSystem/multithread/nativeThreadType.hpp>///nativeThread_type
#include <iostream>///std::cout
#include <unistd.h> //sleep(unsigned seconds);

#define ThreadRetCode 3
///Alternative: const int ThreadRetCode = 3;

DWORD ThreadFunc(void * p_v)
{
  sleep(2);
  ///For Windows API not needed, but for POSIX (Linux etc.) 
  nativeThread_type::SetExitCode((void*)3);
  return ThreadRetCode;
}

int main()
{
  nativeThread_type thread;
  thread.start(ThreadFunc, 0);

  const int termCode = thread.GetTermCode();
  std::cout << "thread exit code:" << termCode << std::endl;

  if(thread.WaitForTermination() == 0)
  {
    const int termCode = thread.GetTermCode();

    std::cout << "thread exit code:" << termCode << std::endl;
    if( termCode != ThreadRetCode)
      std::cerr << "test failed" << std::endl;
    else
      std::cout << "test succeeded" << std::endl;
    return termCode;
  }
  else
    std::cerr << "Error waiting for thread termination." << std::endl;
  return -1;
}

