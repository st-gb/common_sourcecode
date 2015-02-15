#pragma once

#include "GetCurrentTime.h"

#ifdef __cplusplus
namespace OperatingSystem
{
#endif
inline void GetCurrentTime(struct tm & tm_Current)
{
  ::GetCurrentTime(& tm_Current);
}
#ifdef __cplusplus
}
#endif
