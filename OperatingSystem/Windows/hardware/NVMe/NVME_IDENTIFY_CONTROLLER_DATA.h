/**(c)from 2023 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=Berlin: http://www.acronymfinder.com/Berlin-(Bln).html 
 * OpSys=OPerating SYStem: http://www.abbreviations.com/OpSys */\
 ! defined TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_IDENTIFY_CONTROLLER_DATA_h
   #define TU_Bln361095OpSys_Windows_hardware_NVMe_NVME_IDENTIFY_CONTROLLER_DATA_h

///Standard Microsoft Windows header files:
#include <windef.h>///USHORT, UCHAR, ULONG members

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///struct NVME_IDENTIFY_CONTROLLER_DATA's member "PDS"
#include "NVME_POWER_STATE_DESC.h"

/** from:
http://learn.microsoft.com/en-us/windows/win32/api/nvme/ns-nvme-nvme_identify_controller_data
 * : "Header  nvme.h" */
typedef struct {
  USHORT VID;///"Vendor ID"
  USHORT SSVID;
  UCHAR SN[20];///"Serial Number"
  UCHAR MN[40];///"Manufacturer Number" (model name)
  UCHAR FR[8];///"Firmware Revision"
  UCHAR RAB;
  UCHAR IEEE[3];
  struct {
    UCHAR MultiPCIePorts : 1;
    UCHAR MultiControllers : 1;
    UCHAR SRIOV : 1;
    UCHAR ANAR : 1;
    UCHAR Reserved : 4;
  } CMIC;
  UCHAR MDTS;
  USHORT CNTLID;
  ULONG VER;
  ULONG RTD3R;
  ULONG RTD3E;
  struct {
    ULONG Reserved0 : 8;
    ULONG NamespaceAttributeChanged : 1;
    ULONG FirmwareActivation : 1;
    ULONG Reserved1 : 1;
    ULONG AsymmetricAccessChanged : 1;
    ULONG PredictableLatencyAggregateLogChanged : 1;
    ULONG LbaStatusChanged : 1;
    ULONG EnduranceGroupAggregateLogChanged : 1;
    ULONG Reserved2 : 12;
    ULONG ZoneInformation : 1;
    ULONG Reserved3 : 4;
  } OAES;
  struct {
    ULONG HostIdentifier128Bit : 1;
    ULONG NOPSPMode : 1;
    ULONG NVMSets : 1;
    ULONG ReadRecoveryLevels : 1;
    ULONG EnduranceGroups : 1;
    ULONG PredictableLatencyMode : 1;
    ULONG TBKAS : 1;
    ULONG NamespaceGranularity : 1;
    ULONG SQAssociations : 1;
    ULONG UUIDList : 1;
    ULONG Reserved0 : 22;
  } CTRATT;
  struct {
    USHORT ReadRecoveryLevel0 : 1;
    USHORT ReadRecoveryLevel1 : 1;
    USHORT ReadRecoveryLevel2 : 1;
    USHORT ReadRecoveryLevel3 : 1;
    USHORT ReadRecoveryLevel4 : 1;
    USHORT ReadRecoveryLevel5 : 1;
    USHORT ReadRecoveryLevel6 : 1;
    USHORT ReadRecoveryLevel7 : 1;
    USHORT ReadRecoveryLevel8 : 1;
    USHORT ReadRecoveryLevel9 : 1;
    USHORT ReadRecoveryLevel10 : 1;
    USHORT ReadRecoveryLevel11 : 1;
    USHORT ReadRecoveryLevel12 : 1;
    USHORT ReadRecoveryLevel13 : 1;
    USHORT ReadRecoveryLevel14 : 1;
    USHORT ReadRecoveryLevel15 : 1;
  } RRLS;
  UCHAR Reserved0[9];
  UCHAR CNTRLTYPE;
  UCHAR FGUID[16];
  USHORT CRDT1;
  USHORT CRDT2;
  USHORT CRDT3;
  UCHAR Reserved0_1[106];
  UCHAR ReservedForManagement[16];
  struct {
    USHORT SecurityCommands : 1;
    USHORT FormatNVM : 1;
    USHORT FirmwareCommands : 1;
    USHORT NamespaceCommands : 1;
    USHORT DeviceSelfTest : 1;
    USHORT Directives : 1;
    USHORT NVMeMICommands : 1;
    USHORT VirtualizationMgmt : 1;
    USHORT DoorBellBufferConfig : 1;
    USHORT GetLBAStatus : 1;
    USHORT Reserved : 6;
  } OACS;
  UCHAR ACL;
  UCHAR AERL;
  struct {
    UCHAR Slot1ReadOnly : 1;
    UCHAR SlotCount : 3;
    UCHAR ActivationWithoutReset : 1;
    UCHAR Reserved : 3;
  } FRMW;
  struct {
    UCHAR SmartPagePerNamespace : 1;
    UCHAR CommandEffectsLog : 1;
    UCHAR LogPageExtendedData : 1;
    UCHAR TelemetrySupport : 1;
    UCHAR PersistentEventLog : 1;
    UCHAR Reserved0 : 1;
    UCHAR TelemetryDataArea4 : 1;
    UCHAR Reserved1 : 1;
  } LPA;
  UCHAR ELPE;
  UCHAR NPSS;
  struct {
    UCHAR CommandFormatInSpec : 1;
    UCHAR Reserved : 7;
  } AVSCC;
  struct {
    UCHAR Supported : 1;
    UCHAR Reserved : 7;
  } APSTA;
  USHORT WCTEMP;
  USHORT CCTEMP;
  USHORT MTFA;
  ULONG HMPRE;
  ULONG HMMIN;
  UCHAR TNVMCAP[16];
  UCHAR UNVMCAP[16];
  struct {
    ULONG RPMBUnitCount : 3;
    ULONG AuthenticationMethod : 3;
    ULONG Reserved0 : 10;
    ULONG TotalSize : 8;
    ULONG AccessSize : 8;
  } RPMBS;
  USHORT EDSTT;
  UCHAR DSTO;
  UCHAR FWUG;
  USHORT KAS;
  struct {
    USHORT Supported : 1;
    USHORT Reserved : 15;
  } HCTMA;
  USHORT MNTMT;
  USHORT MXTMT;
  struct {
    ULONG CryptoErase : 1;
    ULONG BlockErase : 1;
    ULONG Overwrite : 1;
    ULONG Reserved : 26;
    ULONG NDI : 1;
    ULONG NODMMAS : 2;
  } SANICAP;
  ULONG HMMINDS;
  USHORT HMMAXD;
  USHORT NSETIDMAX;
  USHORT ENDGIDMAX;
  UCHAR ANATT;
  struct {
    UCHAR OptimizedState : 1;
    UCHAR NonOptimizedState : 1;
    UCHAR InaccessibleState : 1;
    UCHAR PersistentLossState : 1;
    UCHAR ChangeState : 1;
    UCHAR Reserved : 1;
    UCHAR StaticANAGRPID : 1;
    UCHAR SupportNonZeroANAGRPID : 1;
  } ANACAP;
  ULONG ANAGRPMAX;
  ULONG NANAGRPID;
  ULONG PELS;
  UCHAR Reserved1[156];
  struct {
    UCHAR RequiredEntrySize : 4;
    UCHAR MaxEntrySize : 4;
  } SQES;
  struct {
    UCHAR RequiredEntrySize : 4;
    UCHAR MaxEntrySize : 4;
  } CQES;
  USHORT MAXCMD;
  ULONG NN;
  struct {
    USHORT Compare : 1;
    USHORT WriteUncorrectable : 1;
    USHORT DatasetManagement : 1;
    USHORT WriteZeroes : 1;
    USHORT FeatureField : 1;
    USHORT Reservations : 1;
    USHORT Timestamp : 1;
    USHORT Verify : 1;
    USHORT Reserved : 8;
  } ONCS;
  struct {
    USHORT CompareAndWrite : 1;
    USHORT Reserved : 15;
  } FUSES;
  struct {
    UCHAR FormatApplyToAll : 1;
    UCHAR SecureEraseApplyToAll : 1;
    UCHAR CryptographicEraseSupported : 1;
    UCHAR FormatSupportNSIDAllF : 1;
    UCHAR Reserved : 4;
  } FNA;
  struct {
    UCHAR Present : 1;
    UCHAR FlushBehavior : 2;
    UCHAR Reserved : 5;
  } VWC;
  USHORT AWUN;
  USHORT AWUPF;
  struct {
    UCHAR CommandFormatInSpec : 1;
    UCHAR Reserved : 7;
  } NVSCC;
  struct {
    UCHAR WriteProtect : 1;
    UCHAR UntilPowerCycle : 1;
    UCHAR Permanent : 1;
    UCHAR Reserved : 5;
  } NWPC;
  USHORT ACWU;
  UCHAR Reserved4[2];
  struct {
    ULONG SGLSupported : 2;
    ULONG KeyedSGLData : 1;
    ULONG Reserved0 : 13;
    ULONG BitBucketDescrSupported : 1;
    ULONG ByteAlignedContiguousPhysicalBuffer : 1;
    ULONG SGLLengthLargerThanDataLength : 1;
    ULONG MPTRSGLDescriptor : 1;
    ULONG AddressFieldSGLDataBlock : 1;
    ULONG TransportSGLData : 1;
    ULONG Reserved1 : 10;
  } SGLS;
  ULONG MNAN;
  UCHAR Reserved6[224];
  UCHAR SUBNQN[256];
  UCHAR Reserved7[768];
  UCHAR Reserved8[256];
  NVME_POWER_STATE_DESC PDS[32];
  UCHAR VS[1024];
} NVME_IDENTIFY_CONTROLLER_DATA, *PNVME_IDENTIFY_CONTROLLER_DATA;

#endif///include guard