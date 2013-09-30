#ifndef AMD_X86
#define AMD_X86

namespace AMD
{
  namespace x86
  {
    enum voltageIDincOrDec{ decrementVoltageID = -1,
      incrementVoltageID = 1 };
    enum incOrDecVoltage{ decrementVoltage = incrementVoltageID, incrementVoltage = decrementVoltageID};
  }
}

#endif 