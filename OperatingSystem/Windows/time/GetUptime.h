#pragma once///Include guard
#include "GetTimeCount.hpp"///Windows_API::GetTimeCountInSeconds(...)

namespace OperatingSystem{
template<typename secType> bool GetUptimeInS(secType & upTimeInS){
  return Windows_API::GetTimeCountInSeconds(upTimeInS);
}
}