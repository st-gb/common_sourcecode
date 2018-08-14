#pragma once /** Include guard */

#include <windows.h> //Sleep(...)

namespace OperatingSystem {
  void suspendExecution(int seconds)
  {
    /** https://docs.microsoft.com/en-us/windows/desktop/api/synchapi/nf-synchapi-sleep :
        unit is milliseconds */
    Sleep(seconds * 1000);
  }
}