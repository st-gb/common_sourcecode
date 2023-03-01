/**(c)from 2022 by Stefan Gebauer,Computer Science Master(TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

#include "CPUFreq.h"///TU_Bln361095cmnSrcOpSysUnixCPUFreqDef

/** Character string for sprintf(...) for creating file system paths for CPU
 *  cores.*/
/*static*/ const char TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(
/**avail=AVAILable:http://www.abbreviations.com/abbreviation/Available
 * Abs=ABSolute:http://www.abbreviations.com/abbreviation/absolute
 * Fmt=ForMaT:http://www.abbreviations.com/abbreviation/format
 * Str=STRing:http://www.abbreviations.com/abbreviation/string */
  availGvrnrsAbsFilePathFmtStr) []=
/**http://www.kernel.org/doc/html/v4.14/admin-guide/pm/cpufreq.html#policy-interface-in-sysfs :
 * : read "/sys/devices/system/cpu/cpu* /cpufreq/scaling_governor" */
  "/sys/devices/system/cpu/cpu%u/cpufreq/scaling_available_governors";
