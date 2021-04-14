/** PDH_DLL_function_signatures.h
 *  Created on: Apr 30, 2010
 *  Author: Stefan Gebauer, M.Sc. Comp.Sc.*/

#ifndef PDH_DLL_FUNCTION_SIGNATURES_H_
#define PDH_DLL_FUNCTION_SIGNATURES_H_

#include <specstrings.h> //for __out_ecount_opt etc. in Pdh.h
#if __GNUC__ > 5 ///Pdh.h not in early MingGW GCC versions?
  #include <pdh.h>///HCOUNTER, HQUERY
#endif

#ifdef __MINGW32__
 ///Defined in 32 bit MinGW (GCC) v. 5, but not in 64 bit MinGW (GCC) v.5
 #ifndef __out_ecount_opt
  #define __out_ecount_opt SAL__out_ecount_opt
 #endif
#endif
//from pdh.h:
//PDH_FUNCTION -> "PDH_STATUS ( __stdcall * ... )"

typedef PDH_STATUS ( __stdcall * PdhAddCounterW_type) (
    __in  PDH_HQUERY     hQuery,
    __in  LPCWSTR        szFullCounterPath,
    __in  DWORD_PTR      dwUserData,
    __out PDH_HCOUNTER * phCounter
);
typedef PDH_STATUS ( __stdcall * PdhAddEnglishCounterW_type) (
  __in  PDH_HQUERY hQuery,
  __in  LPCWSTR szFullCounterPath,
  __in  DWORD_PTR dwUserData,
  __out PDH_HCOUNTER * phCounter
  );
typedef PDH_STATUS ( __stdcall * PdhCloseQuery_type) (
    __inout PDH_HQUERY hQuery
);
typedef PDH_STATUS ( __stdcall * PdhCollectQueryData_type) (
    __inout PDH_HQUERY hQuery
);
typedef PDH_STATUS (  __stdcall * PdhEnumObjectsW_type) (
    __in_opt LPCWSTR szDataSource,
    __in_opt LPCWSTR szMachineName,
    __out_ecount_opt(* pcchBufferSize) PZZWSTR mszObjectList,
    __inout  LPDWORD pcchBufferSize,
    __in     DWORD   dwDetailLevel,
    __in     BOOL    bRefresh
);
typedef PDH_STATUS
  ( __stdcall * PdhGetFormattedCounterValue_type) (
    __in      PDH_HCOUNTER          hCounter,
    __in      DWORD                 dwFormat,
    __out_opt LPDWORD               lpdwType,
    __out     PPDH_FMT_COUNTERVALUE pValue
);
typedef PDH_STATUS
  ( __stdcall * PdhOpenQueryW_type) (
    __in_opt LPCWSTR      szDataSource,
    __in     DWORD_PTR    dwUserData,
    __out    PDH_HQUERY * phQuery
);
typedef PDH_STATUS
  ( __stdcall * PdhLookupPerfNameByIndexW_type ) (
    __in_opt LPCWSTR szMachineName,
    __in     DWORD   dwNameIndex,
    __out_ecount_opt(* pcchNameBufferSize) LPWSTR  szNameBuffer,
    __inout  LPDWORD pcchNameBufferSize
    ) ;

#endif /* PDH_DLL_FUNCTION_SIGNATURES_H_ */
