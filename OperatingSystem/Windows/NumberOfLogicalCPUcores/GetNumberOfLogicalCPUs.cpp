/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
//from http://msdn.microsoft.com/en-us/library/ms683194%28VS.85%29.aspx

//#include "StdAfx.h"
//#include <windef.h> //WINAPI
#include <windows.h> //WINAPI
#include "GetNumberOfLogicalCPUs.h"
#include <preprocessor_macros/logging_preprocessor_macros.h>
#include <stdlib.h> //malloc()
//#include <winnt.h>

/* Works starting from:Windows Vista, Windows XP Professional x64 Edition,
 * Windows XP with SP3 */
//typedef BOOL (WINAPI * LPFN_GetLogicalProcessorInformation)(
//  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
//  PDWORD);
//
//// Helper function to count set bits in the processor mask.
//DWORD CountSetBits(ULONG_PTR bitMask)
//{
//  DEBUGN("bitMask:" << bitMask)
//  DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
//  DWORD bitSetCount = 0;
//  ULONG_PTR bitTest = (ULONG_PTR) 1 << LSHIFT;
//  DWORD i;
//
//  //Compare bitmask with a bitmask that has only 1 bit set moving from the
//  //highmost bit to the lowmost bit.
//  for (i = 0; i <= LSHIFT; ++ i )
//  {
//    bitSetCount += ((bitMask & bitTest) ? 1 : 0 );
//    //Move the set bit 1 bit directing lowmost bit.
//    bitTest /= 2;
//  }
//  DEBUGN("bitSetCount:" << bitSetCount)
//  return bitSetCount;
//}

//TODO reports wrong value ("0") under win XP home-- add error codes for getting
//the cause.
WORD Windows::GetNumberOfLogicalCPUcores()
{
//  LPFN_GetLogicalProcessorInformation p_fn_get_logical_processor_information;
//  BOOL done = FALSE;
//  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ar_system_logical_processor_information
//    = NULL;
//  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION
//    psystem_logical_processor_informationCurrent = NULL;
//  DWORD dwBufferLengthInBytes = 0;
  WORD wNumberOfLogicalCPUcores = 0;
////  DWORD processorCoreCount = 0;
//  DWORD byteOffset = 0;
//
//  p_fn_get_logical_processor_information = (LPFN_GetLogicalProcessorInformation)
//    GetProcAddress(
//    GetModuleHandle( TEXT("kernel32") ),
//    "GetLogicalProcessorInformation"
//    );
  //from http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
  SYSTEM_INFO sysinfo;
  GetSystemInfo( &sysinfo );

  wNumberOfLogicalCPUcores = sysinfo.dwNumberOfProcessors;

  DEBUGN( "# CPU cores via GetSystemInfo:" << wNumberOfLogicalCPUcores)
//  DEBUGN("p_fn_get_logical_processor_information:" <<
//    p_fn_get_logical_processor_information)
//  if (NULL == p_fn_get_logical_processor_information)
//    //GetLogicalProcessorInformation is not supported.
//  {
//    DEBUGN("NULL == p_fn_get_logical_processor_information")
//    return //(0);
//      //no_GetLogicalProcessorInformation_fct;
//      wNumberOfLogicalCPUcores;
//  }
//  while ( ! done )
//  {
//    DWORD rc =
//      //Cites from http://msdn.microsoft.com/en-us/library/
//      //ms683194%28VS.85%29.aspx ("GetLogicalProcessorInformation Function")
//      //"If the function fails, the return value is FALSE"
//      (* p_fn_get_logical_processor_information)(
//        //"A pointer to a buffer that receives an array of
//        // SYSTEM_LOGICAL_PROCESSOR_INFORMATION structures."
//        ar_system_logical_processor_information,
//      //"If the buffer is not large enough to contain all of the data, the
//      //function fails, GetLastError returns ERROR_INSUFFICIENT_BUFFER, and
//      //ReturnLength is set to the buffer length required to contain all of
//      //the data".
//      & dwBufferLengthInBytes //ReturnLength
//      );
//    if (FALSE == rc)
//    {
//      DEBUGN("calling \"GetLogicalProcessorInformation\" failed")
//      if ( GetLastError() == ERROR_INSUFFICIENT_BUFFER )
//      {
//        DEBUGN("GetLastError() == ERROR_INSUFFICIENT_BUFFER")
//        if (ar_system_logical_processor_information)
//          free(ar_system_logical_processor_information);
//        ar_system_logical_processor_information =
//          (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION) malloc(
//          dwBufferLengthInBytes);
//        if (NULL == ar_system_logical_processor_information)
//        {//Error: Allocation failure
//          DEBUGN("allocating " << dwBufferLengthInBytes << " bytes for "
//            "PSYSTEM_LOGICAL_PROCESSOR_INFORMATION failed")
//          return (0);
//        }
//      }
//      else //Error %d\n"), GetLastError()
//      {
//        DEBUGN("GetLastError() != ERROR_INSUFFICIENT_BUFFER")
//        return (0);
//      }
//    }
//    else
//    {
//      done = TRUE;
//    }
//  }
//  //Begin at/ point to the 1st array element.
//  psystem_logical_processor_informationCurrent =
//    ar_system_logical_processor_information;
//
//  while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <=
//    dwBufferLengthInBytes )
//  {
//    switch (psystem_logical_processor_informationCurrent->Relationship)
//    {
//    //case RelationNumaNode:
//    case RelationProcessorCore:
////      processorCoreCount++;
//      // A hyperthreaded core supplies more than one logical processor.
//      wNumberOfLogicalCPUcores += CountSetBits(
//        psystem_logical_processor_informationCurrent->ProcessorMask);
//      break;
//    //case RelationProcessorPackage:
//    default: //Error: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.
//      break;
//    }
//    //The next offset starts at the next array element.
//    byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
//    //Advance to the next array element.
//    psystem_logical_processor_informationCurrent ++;
//  }
////  _tprintf(TEXT("Number of NUMA nodes: %d\n"), numaNodeCount);
////  _tprintf(TEXT("Number of processor cores: %d\n"), processorCoreCount);
//  free(ar_system_logical_processor_information);
  return wNumberOfLogicalCPUcores ;
}
