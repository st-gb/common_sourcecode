#pragma once /** Include guard */

#include <unistd.h> //sleep(unsigned seconds);

namespace OperatingSystem {
  void suspendExecution(int seconds)
  {
    /** https://linux.die.net/man/3/sleep */
    sleep(seconds);
  }
}