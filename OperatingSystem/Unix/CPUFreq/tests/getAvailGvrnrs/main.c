///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)

///Standard C header files:
#include <stdio.h>///printf(...)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include "../../getAvailGvrnrs.h"///TU_Bln361095CPUFreqUse(GetAvailGvrnrs)

//#define TU_Bln361095getAvailCPUFreqGvrnrsRtrnCodeDef(suffix)
//enum RtrnCodes{
//  TU_Bln361095getAvailCPUFreqGvrnrsRtrnCodeDef(Success),
//  };

/**@brief Retrieves available CPUFreq governors and prints them to standard
 *  output (usually console)
 * 
 * @return 0=success, else error */
int main()
{
  TU_Bln361095CPUuse(FaststUint) numGvrnrs;
  char ** availGvrnrsArr;
  enum TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(E)
    getAvailGvrnrsRslt = TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(GetAvailGvrnrs)(
      0, &numGvrnrs, &availGvrnrsArr);
  if(getAvailGvrnrsRslt ==
     TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(Sccss) )
  {
    printf("Number of CPUFreq governors for CPU core 0:%u\n", numGvrnrs);
    printf("CPUFreq governors:\n");
    for(TU_Bln361095CPUuse(FaststUint) gvrnrIdx = 0;gvrnrIdx < numGvrnrs;
      gvrnrIdx++)
    {
      printf("-\"%s\"\n", availGvrnrsArr[gvrnrIdx]);
    }
  }
  else
  {
    printf("Error getting available CPUFreq governors.\n");
    switch(getAvailGvrnrsRslt)
    {
      case TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(OpnFlFaild):
      case TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(GetFlSzFaild):
      case TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(RdFlFaild):
      case TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(SkFlFaild):
      {///Block is needed for local variables in "case" branch.
        size_t availGvrnrsAbsFilePathNumChars = strlen(
          TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(availGvrnrsAbsFilePathFmtStr) )
          + maxNumDecDigitsFor16BitIntPlusTerm0Char;
        char availGvrnrsAbsFilePath[availGvrnrsAbsFilePathNumChars];
        snprintf(availGvrnrsAbsFilePath, availGvrnrsAbsFilePathNumChars,
          TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(availGvrnrsAbsFilePathFmtStr),
          0);
        printf("%s: File:\"%s\"\n",
          TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(EnMsgsA)[
            getAvailGvrnrsRslt], availGvrnrsAbsFilePath);
        return getAvailGvrnrsRslt;
      }
      default:
        printf("%s\n",
          TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(EnMsgsA)[
            getAvailGvrnrsRslt]);
        return getAvailGvrnrsRslt;
    }
  }
  return 0;
}
