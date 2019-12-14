#pragma once //include guard
#ifndef POWERPROFACCESSFROMWIN6_H_
  #define POWERPROFACCESSFROMWIN6_H_

//#define INCLUDE_POWRPROF_H_IN_PWRPROFDYNLINKED_FROM_VER6_H
//If the powrprof.h for Windows version >= 6 is already included
//MS compiler: "error C2011: '_POWER_DATA_ACCESSOR' : 'enum' type redefinition"
#ifdef INCLUDE_POWERPROF_FOR_WINDOWS_ABOVE_VERSION6
#include "../PowerProf_From_Win6.h"
//#else
#ifdef INCLUDE_POWRPROF_H_IN_PWRPROFDYNLINKED_FROM_VER6_H
//#ifdef __CYGWIN__ // pwrprof.h != PowerProf.h in gcc (->case matters)
    //Causes multiple definitions of structs if also included afterwards.
    #include <powrprof.h> // for PowerWriteACValueIndex()
//#elif defined (_MSC_VER )
////This must be the PowrProf.h from the Windows (platform) SDK for Vista,
////ie. SDK version >= "6" / "6.1" .
//#include <PowrProf.h> // for PowerWriteACValueIndex()
//#endif
#endif //#ifdef INCLUDE_POWRPROF_H_IN_PWRPROFDYNLINKED_FROM_VER6_H
#endif //#ifdef INCLUDE_POWERPROF_FOR_WINDOOWS_ABOVE_VERSION6

#include <Controller/character_string/stdtstr.hpp> //for std::tstring

#ifndef _MSC_VER //if not an MS-compiler
//Not all MinGW versions provide <specstrings.h> .
#ifdef INCLUDE_SPECSTRINGS_H
  //#if defined( __MINGW32__) || (__GNUC__>=4)
    #include <specstrings.h> //for "__in_opt" preprocessor macro etc.
  //#else
    #include <specstrings_strict.h>
  //#endif
#else //#ifdef INCLUDE_SPECSTRINGS_H
  //Defining only the macros needed in this file here is a little bit faster
  //than including all specstrings.h macros.
  #define __deref_out
  #define __in
  #define __in_opt
  #define __inout
  #define __out
  #define __out_opt
#endif //#ifdef INCLUDE_SPECSTRINGS_H
  typedef DWORD far           * LPDWORD;
#endif
#include <set> //std::set

#include "PowerProfFromWin6_DLL_functions_definitions.h"

//class IDynFreqScalingAccess ;
#include <Controller/IDynFreqScalingAccess.hpp>
//#include <Windows/PowerProfDynLinked.hpp>
#include "../I_PowerProfDynLinked.hpp"

class DLLfunctionPointerNotAssignedException
{
};

class PowerProfFromWin6DynLinked
  : //public IDynFreqScalingAccess
  //public PowerProfDynLinked
  //, 
  public I_PowerProfDynLinked
{
  bool m_bActivePowerSchemeAssigned ;
  bool m_bThrottleSettingsAssigned ;
  DWORD m_dwACProcThrottleMaxValue ;
  DWORD m_dwACProcThrottleMinValue ;
  DWORD m_dwDCProcThrottleMaxValue ;
  DWORD m_dwDCProcThrottleMinValue ;
  GUID m_guidPowerSchemeBeforeDisabling ;
  GUID m_guidPowerSchemeToSet ;
  GUID * mp_guidPowerSchemeBeforeDisabling ;
  HINSTANCE m_hinstancePowerProfDLL ;
  pfnPowerDeleteScheme m_pfnpowerdeletescheme ;
  pfnPowerDuplicateScheme m_pfnpowerduplicatescheme ;
  pfnPowerEnumerate m_pfnpowerenumerate ;
  pfnPowerGetActiveScheme m_pfnpowergetactivescheme ;
  pfnPowerReadACValueIndex m_pfnpowerreadacvalueindex ;
  pfnPowerReadACValueIndex m_pfnpowerreaddcvalueindex ;
  pfnPowerReadFriendlyName m_pfnpowerreadfriendlyname ;
  pfnPowerSetActiveScheme m_pfnpowersetactivescheme ;
  pfnPowerSettingAccessCheck m_pfnpowersettingaccesscheck ;
  pfnPowerWriteACValueIndex m_pfnpowerwriteacvalueindex ;
  pfnPowerWriteACValueIndex m_pfnpowerwritedcvalueindex ;
  pfnPowerWriteFriendlyName m_pfnpowerwritefriendlyname ;
public:
  BYTE ActivatePowerSchemeToSet() ;
  bool ChangeOtherDVFSaccessPossible ()
  {
    //DWORD dwRet ;
    //maybe PowerCanRestoreIndividualDefaultPowerScheme(...) is
    //appropriate.
    return true ;
    ////http://msdn.microsoft.com/en-us/library/aa372676%28VS.85%29.aspx:
    ////PowerSettingAccessCheck(...)" is the equivalent fucntion for 
    ////Windows < version 6's "CanUserWritePwrScheme(...) function.
    //dwRet = PowerSettingAccessCheck(ACCESS_SCHEME, NULL) ;
    //return dwRet == ERROR_SUCCESS ;
  }
  BYTE CreatePowerScheme(
    const std::wstring & cr_stdtstrPowerSchemeName
    , DWORD & r_dwRetValue
    , GUID & guidNewPowerScheme ) ;
  unsigned char CreatePowerSchemeWithWantedName() ;
  BYTE DeletePowerScheme( 
    //const std::tstring & cr_stdtstrPowerSchemeName
    //Power scheme names are in wide char for Win XP etc.
    const std::wstring & cr_std_wstrPowerSchemeName
    ) ;
  BYTE DisableDVFSforAlternateCurrent(
    const GUID * cp_guidPowerScheme
    , DWORD dwProcThrottleValue ) ;
  BYTE DisableDVFSforDirectCurrent(
    const GUID * cp_guidPowerScheme
    , DWORD dwProcThrottleValue ) ;
  BYTE DisableDVFSforPowerSchemeToSet() ;
  //Inherited from class PowerProfDynLinked.
//  bool DisableFrequencyScalingByOS() ;
  unsigned char EnableFrequencyScalingByOS() ;
  bool EnablingIsPossible() ;

  void GetThrottleSettings(
    const GUID & guidActivePowerScheme
    , DWORD & dwACProcThrottleMaxValue
    , DWORD & dwACProcThrottleMinValue 
    , DWORD & dwDCProcThrottleMaxValue 
    , DWORD & dwDCProcThrottleMinValue 
    ) ;

  IDynFreqScalingAccess::string_type GetEnableDescription() ;

  void GetActivePowerSchemeName(
    std::wstring & r_stdwstrActivePowerSchemeName) ;
  void GetAllPowerSchemeNames(std::set<std::wstring> &
      stdset_stdwstrPowerSchemeName ) ;
  DWORD GetPowerSchemeName(
    GUID & guidPowerScheme , std::wstring & r_stdwstr ) ;

  DWORD PowerDeleteScheme(
    __in_opt  HKEY RootPowerKey,
    __in      const GUID *SchemeGuid
  );
  DWORD WINAPI PowerDuplicateScheme(
    __in_opt  HKEY RootPowerKey,
    __in      const GUID *SourceSchemeGuid,
    __in      GUID **DestinationSchemeGuid
  );

  DWORD WINAPI PowerEnumerate(
    __in_opt   HKEY RootPowerKey,
    __in_opt   const GUID *SchemeGuid,
    __in_opt   const GUID *SubGroupOfPowerSettingsGuid,
    __in       POWER_DATA_ACCESSOR AccessFlags,
    __in       ULONG Index,
    __out_opt  UCHAR *Buffer,
    __inout    DWORD *BufferSize
  );
  DWORD PowerEnumerate(
    __in_opt   GUID *SchemeGuid,
    __in_opt   const GUID *SubGroupOfPowerSettingsGuid,
    __in       POWER_DATA_ACCESSOR AccessFlags,
    __in       ULONG Index,
    //A pointer to a variable to receive the elements. If this parameter is NULL, the function retrieves the size of the buffer required.
    UCHAR * & Buffer
    ) ;
  DWORD
  WINAPI
  PowerGetActiveScheme (
    __in_opt HKEY UserRootPowerKey,
    __deref_out GUID **ActivePolicyGuid
    ) ;
  DWORD
  WINAPI
  PowerGetActiveScheme (
    __in_opt HKEY UserRootPowerKey,
    __deref_out GUID & ActivePolicyGuid
    ) ;
  //avoid g++ warning "`class PowerProfFromWin6DynLinked' has virtual
  // functions but non-virtual destructor"
  ~PowerProfFromWin6DynLinked() { }
  DWORD WINAPI PowerReadACValueIndex (
    __in_opt HKEY RootPowerKey,
    __in_opt CONST GUID *SchemeGuid,
    __in_opt CONST GUID *SubGroupOfPowerSettingsGuid,
    __in_opt CONST GUID *PowerSettingGuid,
    __out LPDWORD AcValueIndex
    ) ;
  DWORD WINAPI PowerReadDCValueIndex (
    __in_opt HKEY RootPowerKey,
    __in_opt CONST GUID *SchemeGuid,
    __in_opt CONST GUID *SubGroupOfPowerSettingsGuid,
    __in_opt CONST GUID *PowerSettingGuid,
    __out LPDWORD AcValueIndex
    ) ;
  DWORD WINAPI PowerReadFriendlyName(
    __in_opt   const GUID *SchemeGuid,
    __in_opt   const GUID *SubGroupOfPowerSettingsGuid,
    __in_opt   const GUID *PowerSettingGuid,
    //A pointer to a variable to receive the elements. If this parameter is NULL,
    //the function retrieves the size of the buffer required.
    UCHAR * & Buffer
    ) ;
  DWORD WINAPI PowerReadFriendlyName(
    __in_opt   HKEY RootPowerKey,
    __in_opt   const GUID *SchemeGuid,
    __in_opt   const GUID *SubGroupOfPowerSettingsGuid,
    __in_opt   const GUID *PowerSettingGuid,
    __out_opt  PUCHAR Buffer,
    __inout    LPDWORD BufferSize
  );
  DWORD WINAPI PowerSetActiveScheme(
    __in_opt  HKEY UserRootPowerKey,
    __in      const GUID *SchemeGuid
  );
  DWORD WINAPI PowerSettingAccessCheck(
    __in      POWER_DATA_ACCESSOR AccessFlags,
    __in_opt  const GUID *PowerGuid
    );
  DWORD WINAPI PowerWriteACValueIndex(
    __in_opt  HKEY RootPowerKey,
    __in      const GUID *SchemeGuid,
    __in_opt  const GUID *SubGroupOfPowerSettingsGuid,
    __in_opt  const GUID *PowerSettingGuid,
    __in      DWORD DcValueIndex
    );
  BYTE PowerSchemeToSetExists() ;
  DWORD WINAPI PowerWriteDCValueIndex(
    __in_opt  HKEY RootPowerKey,
    __in      const GUID *SchemeGuid,
    __in_opt  const GUID *SubGroupOfPowerSettingsGuid,
    __in_opt  const GUID *PowerSettingGuid,
    __in      DWORD DcValueIndex
  );
  DWORD WINAPI PowerWriteFriendlyName(
    __in_opt  HKEY RootPowerKey,
    __in      const GUID *SchemeGuid,
    __in_opt  const GUID *SubGroupOfPowerSettingsGuid,
    __in_opt  const GUID *PowerSettingGuid,
    __in      UCHAR *Buffer,
    __in      DWORD BufferSize
  );
  void InitializeFunctionPointers();
  bool OtherDVFSisEnabled() ;
  PowerProfFromWin6DynLinked(
    std::wstring & r_stdwstrPowerSchemeName
//    std::tstring & r_stdtstrPowerSchemeName
    ) ;
//  void OutputAllPowerSchemes() ;
  //BYTE
  DWORD SetActivePowerScheme(
    const std::wstring & r_stdwstrPowerSchemeName ) ;
  void SetFunctionPointersToNULL() ;
};//end class

#endif //#ifndef POWERPROFACCESSFROMWIN6_H_
