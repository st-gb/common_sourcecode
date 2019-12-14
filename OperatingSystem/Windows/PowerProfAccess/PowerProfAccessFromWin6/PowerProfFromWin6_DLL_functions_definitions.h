#pragma once //include guard

//#include <powrprof.h>///POWER_DATA_ACCESSOR
//Following function pointer types equal the PwrProf API except that they
//are function pointers ("WINAPI *").

///From MinGW's <powrprof.h>:
typedef enum _POWER_DATA_ACCESSOR {
  ACCESS_AC_POWER_SETTING_INDEX   = 0,   // 0x0
  ACCESS_DC_POWER_SETTING_INDEX   = 1,   // 0x1
  ACCESS_SCHEME                   = 16,  // 0x10
  ACCESS_SUBGROUP                 = 17,  // 0x11
  ACCESS_INDIVIDUAL_SETTING       = 18,  // 0x12
  ACCESS_ACTIVE_SCHEME            = 19,  // 0x13
  ACCESS_CREATE_SCHEME            = 20   // 0x14
} POWER_DATA_ACCESSOR, *PPOWER_DATA_ACCESSOR;

typedef DWORD (WINAPI * pfnPowerDeleteScheme) (
  __in_opt  HKEY RootPowerKey,
  __in      const GUID *SchemeGuid
);

typedef DWORD (WINAPI * pfnPowerDuplicateScheme) (
  __in_opt  HKEY RootPowerKey,
  __in      const GUID *SourceSchemeGuid,
  __in      GUID **DestinationSchemeGuid
);

typedef DWORD (WINAPI * pfnPowerEnumerate) (
  __in_opt   HKEY RootPowerKey,
  __in_opt   const GUID *SchemeGuid,
  __in_opt   const GUID *SubGroupOfPowerSettingsGuid,
  __in       POWER_DATA_ACCESSOR AccessFlags,
  __in       ULONG Index,
  __out_opt  UCHAR *Buffer,
  __inout    DWORD *BufferSize
);

typedef DWORD (WINAPI * pfnPowerGetActiveScheme) (
      __in_opt HKEY UserRootPowerKey,
      __deref_out GUID **ActivePolicyGuid
      ) ;

typedef DWORD (WINAPI * pfnPowerReadACValueIndex) (
  __in_opt HKEY RootPowerKey,
  __in_opt CONST GUID *SchemeGuid,
  __in_opt CONST GUID *SubGroupOfPowerSettingsGuid,
  __in_opt CONST GUID *PowerSettingGuid,
  __out LPDWORD AcValueIndex
  ) ;

typedef DWORD ( WINAPI * pfnPowerReadFriendlyName) (
  __in_opt   HKEY RootPowerKey,
  __in_opt   const GUID *SchemeGuid,
  __in_opt   const GUID *SubGroupOfPowerSettingsGuid,
  __in_opt   const GUID *PowerSettingGuid,
  __out_opt  PUCHAR Buffer,
  __inout    LPDWORD BufferSize
);

typedef DWORD ( WINAPI * pfnPowerSetActiveScheme) (
  __in_opt  HKEY UserRootPowerKey,
  __in      const GUID *SchemeGuid
);

typedef DWORD (WINAPI * pfnPowerSettingAccessCheck) (
  __in      POWER_DATA_ACCESSOR AccessFlags,
  __in_opt  const GUID *PowerGuid
);

typedef DWORD (WINAPI * pfnPowerWriteACValueIndex) (
  __in_opt  HKEY RootPowerKey,
  __in      const GUID *SchemeGuid,
  __in_opt  const GUID *SubGroupOfPowerSettingsGuid,
  __in_opt  const GUID *PowerSettingGuid,
  __in      DWORD DcValueIndex
  );
typedef DWORD (WINAPI * pfnPowerWriteFriendlyName) (
  __in_opt  HKEY RootPowerKey,
  __in      const GUID *SchemeGuid,
  __in_opt  const GUID *SubGroupOfPowerSettingsGuid,
  __in_opt  const GUID *PowerSettingGuid,
  __in      UCHAR *Buffer,
  __in      DWORD BufferSize
);
