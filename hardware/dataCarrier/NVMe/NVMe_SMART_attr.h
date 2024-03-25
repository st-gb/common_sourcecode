/** @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

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
/**Include guard supported by (nearly) all compilers:*/\
/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * attr=ATTRibute http://www.abbreviations.com/abbreviation/Attribute */\
 !defined TU_Bln361095cmnSrc_hardware_dataCarrier_NVMe_NVMe_SMART_attr_h
  #define TU_Bln361095cmnSrc_hardware_dataCarrier_NVMe_NVMe_SMART_attr_h  

///Stefan Gebauer's(TU Berlin mat.#361095) ~"common_sourcecode"repository files:
 ///TU_Bln361095hardwareDataCarrierNVMeUse
#include <hardware/dataCarrier/NVMe/NVMe_ID_prefix.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095dataCarrierNVMeSMARTattrDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095dataCarrierNVMeSMARTattrNmSpc\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]NVMeSMARTattrNmSpc" */\
    TU_Bln361095dataCarrierNVMeNmSpc :: SMART :: Attr
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095hardwareDataCarrierNVMeSMARTattrNmSpcBgn\
    TU_Bln361095hardwareDataCarrierNVMeNmSpcBgn\
    namespace SMART{namespace Attr{
  #define TU_Bln361095dataCarrierNVMeSMARTattrNmSpcBgn\
    TU_Bln361095dataCarrierNVMeNmSpcBgn namespace SMART{namespace Attr{
  #define TU_Bln361095hardwareDataCarrierNVMeSMARTattrNmSpcEnd\
      TU_Bln361095hardwareDataCarrierNVMeNmSpcEnd }}
  #define TU_Bln361095dataCarrierNVMeSMARTattrNmSpcEnd\
      TU_Bln361095dataCarrierNVMeNmSpcEnd }}
  #define TU_Bln361095dataCarrierNVMeSMARTattrUse(suffix)\
    TU_Bln361095dataCarrierNVMeSMARTattrNmSpc :: suffix
#else
  #define TU_Bln361095dataCarrierNVMeSMARTattrDef(suffix) suffix
  #define TU_Bln361095dataCarrierNVMeSMARTattrUse(suffix)\
    TU_Bln361095dataCarrierNVMeSMARTattrDef(suffix)
#endif

TU_Bln361095dataCarrierNVMeSMARTattrNmSpcBgn

/**See T13 (t13.org: search for"SMART" result: "SMART Attribute Descriptions
 * (SAD)" ) /
http://media.kingston.com/support/downloads/MKP_521.6_SMART-DCP1000_attribute.pdf
 : "Byte Index": "47:32" */
#define TU_Bln361095dataCarrierNVMeSMARTattrNumRawValB 16
#define TU_Bln361095dataCarrierNVMeSMARTattrNum1stAttrsRawValB 1
  //"Byte Index": "2:1"
#define TU_Bln361095dataCarrierNVMeSMARTattrNumCompTempRawValB 2
/**See
http://en.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#Known_NVMe_S.M.A.R.T._attributes
 */
enum TU_Bln361095dataCarrierNVMeSMARTattrDef(ID){
  TU_Bln361095dataCarrierNVMeSMARTattrDef(CriticalWarning) = 1,
  TU_Bln361095dataCarrierNVMeSMARTattrDef(CompositeTemperature),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(AvailableSpare),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(AvailableSpareThreshold),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(PercentageUsed),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(TotalDataRead) = 6,
  TU_Bln361095dataCarrierNVMeSMARTattrDef(TotalDataWritten),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(HostReadCmds),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(HostWriteCmds),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(ControllerBusyTime),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(PowerCycle),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(PowerOnHours),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(UnsafeShutdowns),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(MediaErrors),
  TU_Bln361095dataCarrierNVMeSMARTattrDef(ErrorInfoLogEntryCount)
  };

struct TU_Bln361095dataCarrierNVMeSMARTattrDef(Def){
  enum TU_Bln361095dataCarrierNVMeSMARTattrUse(ID) ID;
  const char * const name;
};

//extern TU_Bln361095dataCarrierNVMeSMARTattrUse(Def)
//  TU_Bln361095dataCarrierNVMeSMARTattrDef(Defs)[];

TU_Bln361095dataCarrierNVMeSMARTattrNmSpcEnd

#endif///include guard
