/**(c)from 2017 Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)
 * Created on 2. Januar 2017, 23:36 */

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
/**Include guard supported by (nearly) all compilers*/\
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source */\
 !defined TU_Bln361095cmnSrc_hardware_dataCarrier_SMARTattributeNames_h
  #define TU_Bln361095cmnSrc_hardware_dataCarrier_SMARTattributeNames_h

/**TU_Bln361095dataCarrierSMARTdef, TU_Bln361095dataCarrierSMARTnmSpc,
 * TU_Bln361095dataCarrierSMARTnmSpcBgn,
 * TU_Bln361095dataCarrierSMARTattrNmSpcEnd */
#include "SMART/SMART_ID_prefix.h"

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
 /**attr=ATTRibute: http://www.abbreviations.com/abbreviation/Attribute
  * Nm=NaMe: http://www.abbreviations.com/abbreviation/name */
/**Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
 * Put Definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095dataCarrierSMARTattrDef(suffix) suffix
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095dataCarrierSMARTattrNmSpc\
/** Do not append "::" right of the rightmost namespace name to enable
 * "using namespace [...]SMARTattrNmSpc" */\
    TU_Bln361095dataCarrierSMARTnmSpc :: Attr
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095dataCarrierSMARTattrNmSpcBgn\
    TU_Bln361095dataCarrierSMARTnmSpcBgn namespace Attr{
  #define TU_Bln361095dataCarrierSMARTattrNmSpcEnd\
    TU_Bln361095dataCarrierSMARTnmSpcEnd }
  #define TU_Bln361095SMARTattrNmUse(suffix) TU_Bln361095SMARTattrNmNmSpc ::\
    suffix
#else
///Def=DEFinition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095dataCarrierSMARTattrDef(suffix)\
    TU_Bln361095dataCarrierSMARTdef(\
/**http://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation :"The ‘##’
 * preprocessing operator performs token pasting. When a macro is expanded, the
 * two tokens on either side of each ‘##’ operator are combined into a single
 * token, which then replaces the ‘##’ and the two original tokens in the macro
 * expansion."*/\
      attr##suffix)
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/Space
 * "C" language has no namespaces->Replace with empty character string. */
  #define TU_Bln361095SMARTattrNmNmSpc /**->empty*/
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095SMARTattrNmNmSpcBgn /**->empty*/
  #define TU_Bln361095SMARTattrNmNmSpcEnd /**->empty*/
  #define TU_Bln361095SMARTattrNmUse(suffix) TU_Bln361095SMARTattrNmDef(suffix)
#endif

/**Place it in "dataCarrier" namespace because "SMART" may also have other
 * meanings/related to other topics than data carrier.*/
TU_Bln361095dataCarrierSMARTattrNmSpcBgn

/** See https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes */
enum TU_Bln361095dataCarrierSMARTattrDef(ID)
{
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#%C3%9Cbliche_Parameter
   * : "Nicht korrigierbare Fehler beim Lesen von der Festplatte, führt zum 
   * erneuten Einlesen. Deutet auf Problem mit der Plattenoberfläche hin."*/
  TU_Bln361095dataCarrierSMARTattrDef(ReadErrorRate) = 1,
  /**https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   * "Average time of spindle spin up (from zero RPM to fully operational
   * [milliseconds])." */
  TU_Bln361095dataCarrierSMARTattrDef(SpinUpTime) = 3,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    StrtStpCnt) = 4,
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#%C3%9Cbliche_Parameter
   * : "Anzahl der verbrauchten Reservesektoren."*/
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    ReallocSectorsCnt) = 5,
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#.C3.9Cbliche_Parameter
   * : "-Laufleistung in Stunden oder Sekunden (inklusive Standby)
   * -Deutet auf Abnutzung hin, sagt aber nichts über Nutzungsumstände in dieser
   *   Zeit aus.
   * -Bei einigen Modellen von Maxtor, z. B. bei der Maxtor DiamondMax 10 6L250S0 
   *  sind das Minuten." */
  TU_Bln361095dataCarrierSMARTattrDef(PowerOnTime) = 9,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   *  "Count of retry of spin start attempts." */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    SpinUpRetryCnt) = 10,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "This attribute indicates the count that recalibration was requested (under
   * the condition that the first attempt was unsuccessful). An increase of this
   * attribute value is a sign of problems in the hard disk mechanical
   * subsystem." */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    RecalibRetriesOrCalibrRetryCnt) = 11,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Pwr=PoWeR: http://www.abbreviations.com/abbreviation/Power
     * Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    PwrCycleCnt) = 12,
  /** https://media.kingston.com/support/downloads/MKP_306_SMART_attribute.pdf
   * Unit can be determined by comparing to data written by OS?/
   * by getting the block numbers used when written (see "blktrace"--columns
   *  "start block" & "number of blocks" when write events) 
   *  https://git.kernel.dk/?p=blktrace.git;a=blob;f=blkparse_fmt.c;h=df2f6ce2148a473e20f5cd9afd381f0021bfd42d;hb=HEAD :
   *  is in "char *act" of "process_default" called from process_fmt 
     handle_notify 
    https://docs.huihoo.com/doxygen/linux/kernel/3.7/uapi_2linux_2blktrace__api_8h_source.html 
   https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwiGlt3f-c_qAhWPYsAKHZvXC7AQFjAFegQIBxAB&url=https%3A%2F%2Fcodesearch.isocpp.org%2Factcd19%2Fmain%2Fb%2Fblktrace%2Fblktrace_1.2.0-5%2Fblkiomon.c&usg=AOvVaw1nOLy95Q6Y-ixpgB8Krv1o
   */
  TU_Bln361095dataCarrierSMARTattrDef(GiB_Erased) = 100,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   *  e.g. version from 06:41, 22 May 2021‎ :
   *  "The total number of flash program operation failures since the drive was
   *   deployed.[36] Identical to attribute 181."
   *  (if manufacturer is "Kingston") */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    SSDprogFailCnt) = 171,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   *  e.g. version from 06:41, 22 May 2021‎ :
   *  "Counts the number of flash erase failures. This attribute returns the
   *   total number of Flash erase operation failures since the drive was
   *   deployed. This attribute is identical to attribute 182."
   *   (if manufacturer is "Kingston") */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    SSDeraseFailCnt) = 172,
  TU_Bln361095dataCarrierSMARTattrDef(
    ///Pwr=PoWeR: http://www.abbreviations.com/abbreviation/Power
    PwrLossProtectionFailure) = 175,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   *  e.g. version from 06:41, 22 May 2021‎ :
   *  "S.M.A.R.T. parameter indicates a number of flash erase command failures.
   *  [38]" */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cmd=CoMmanD: http://www.abbreviations.com/abbreviation/Command
     * Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    EraseCmdFailCnt) = 176,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   *  e.g. version from 06:41, 22 May 2021‎ :
   *  Either:
   *  -"Total number of Flash program operation failures since the drive was
   *    deployed."
   *  -"Number of user data accesses (both reads and writes) where LBAs are not
   *    4 KiB aligned (LBA % 8 != 0) or where size is not modulus 4 KiB (block
   *    count != 8), assuming logical block size (LBS) = 512 B" */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    PrgramFailCntTotalORnon4KAlignedAccssCnt) = 181,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   *  e.g. version from 06:41, 22 May 2021‎ :
   *  ""Pre-Fail" Attribute used at least in Samsung devices." */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    EraseFailCnt) = 182,
  TU_Bln361095dataCarrierSMARTattrDef(EndToEndError) = 184,
  TU_Bln361095dataCarrierSMARTattrDef(ReportedUncorrError) = 187,
  TU_Bln361095dataCarrierSMARTattrDef(CmdTimeout) = 188,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "[...] recording head is flying outside its normal operating range [...]"*/
  TU_Bln361095dataCarrierSMARTattrDef(HighFlyWrites) = 189,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "Value is equal to (100-temp. °C), [...]
   * However, some older drives may instead report raw Temperature
   * (identical to 0xC2) or Temperature minus 50 here."
   * model:ST9500420AS firmware:0003SDM1 (serial:5VJ1WXTF) :10 CF 2F 2A 00 2F h:
   * -GSmartControl v.0.8.7:47d(2Fh)°C current,42d(2Ah)°C min.,47d(2Fh)°C max.
   * -values are in °C
   * -min.(3rd lowmost byte) and max. (4th lowmost byte) values are since
   *  startup/resume from standby/increase of PwrCycleCnt / StrtStpCnt because
   *  max. value (4th lowmost byte) increases since startup and min. value
   * (3rd lowmost byte) was lower after resume from standby. */
  TU_Bln361095dataCarrierSMARTattrDef(TempDiffOrAirflowTemp) = 190,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "The count of errors resulting from externally induced shock and
   *  vibration." */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    G_senseErrorCnt) = 191,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   *  e.g. version from 06:41, 22 May 2021‎ :
   *  "Indicates the device temperature, if the appropriate sensor is fitted.
   *  Lowest byte of the raw value contains the exact temperature value (Celsius
   *  degrees).[60]" 
   *  Bytes higher than 2nd byte may be min./max.value while the drive is on. :
   *  -model:SAMSUNG HA200JC firmware:WS100-33 (serial:S091J10Y727530) has no
   *   min./max. values (3rd-6th byte is 0) */
  TU_Bln361095dataCarrierSMARTattrDef(
    ///Dev=DEVice: http://www.abbreviations.com/abbreviation/device
    DevTemp) = 194,
  /** model:SAMSUNG HA200JC firmware:WS100-33 (serial:S091J10Y727530):
   *  After startup/1 power cycle count (S.M.A.R.T. ID 12) ? this value is 0.
   *  After reset/ start/stop Count (S.M.A.R.T. ID 4) increase it is the same
   *  value as before reset? */
  TU_Bln361095dataCarrierSMARTattrDef(HW_ECC_Recovered) = 195,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    ReallocEvtCnt) = 196,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Curr=CURRent: http://www.abbreviations.com/abbreviation/Current
     * Sec=SECtor: http://www.abbreviations.com/abbreviation/sector
     * Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    CurrPendSecCnt) = 197,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Sec=SECtor: http://www.abbreviations.com/abbreviation/sector
     * Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    UncorrSecCnt) = 198,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    UDMA_CRCerrorCnt) = 199,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   * "The count of errors found when writing a sector. The higher the value, the
   *  worse the disk's mechanical condition is." */ 
  TU_Bln361095dataCarrierSMARTattrDef(MultiZoneErrorRate) = 200,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes : 
   *  "Count indicates the number of uncorrectable software read errors." */
  TU_Bln361095dataCarrierSMARTattrDef(SoftReadErrorRateOrTACnterDetected) = 201,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   * "A recording of shock encountered during write operations."*/
  TU_Bln361095dataCarrierSMARTattrDef(ShockDuringWrite) = 212,
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Avg=AVeraGe: http://www.abbreviations.com/abbreviation/Average
     * Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    AvgEraseCntAndMaxEraseCnt) = 234,
  /**https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "Time spent during the positioning of the drive heads. Some Fujitsu 
   *  drives report the count of link resets during a data transfer. 
   * Seen for a model "ST9500420AS" firmware "0003SDM1":only the lowmost (>=2)
   * bytes are relevant. The 2 highmost bytes changed fastly, unknown meaning.*/
  TU_Bln361095dataCarrierSMARTattrDef(HeadFlyingHours) = 240,
  /**https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
    241 0xF1 "Total LBAs Written" "Total count of LBAs written." */
  /**Value seems to be gigabytes for the SSD model FS256G39TND-N210A 
   * firmware:30001P10 (serial:EJ7CN55981080CH09) because the value is 440k337
   * after 627 days 17 h Power-On Hours and 87380824 kB ~=87 GB written to disk
   * (via "iostat/dev/sda" Unix command) after 9 days and 20 h uptime.*/
  //see http://www.virten.net/2016/12/ssd-total-bytes-written-calculator/
  /**To get the real unit call hardware::dataCarrier::
   *  getNumBwrittenSinceOSstart(...);
   * (<hardware/dataCarrier/getNumBwrittenSinceOSstart.hpp> from 
   *   git repository "common_sourcecode")
   * If this S.M.A.R.T. value increases:
   *  -then this is point in time "t1"
   *  -memorize current value from getNumBwrittenSinceOSstart(...)
   * Then if this S.M.A.R.T. value increases again:
   *  -then this is point in time "t2"
   * Then "#B written since OS start at t2"-"#B written since OS start at t1" =
   *  "# B written since OS start diff"
   * S.M.A.R.T. value at "t2" - S.M.A.R.T. value at "t1"=S.M.A.R.T. value diff
   *  unit ~= "# B written since OS start diff" / "S.M.A.R.T. value diff" */
  TU_Bln361095dataCarrierSMARTattrDef(
    ///"Data" because unit is not always "LBA"
    TotalDataWritten) = 241,
  /** model:ST9500420AS firmware:0003SDM1 serial #:5VJ1WXTF counted backwards :
   * GSmartControl v.0.8.7 :
   * -1471557884 at 9183 "Power_On_Hours" (S.M.A.R.T. ID 9)
   * -1006509816 at 9186 "Power_On_Hours" (S.M.A.R.T. ID 9)
   * (value overflow->negative interpreted as postive value? or other error?) */
  TU_Bln361095dataCarrierSMARTattrDef(
    ///"Data" because unit is not always "LBAs"
    TotalDataRead) = 242,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "Count of "Free Fall Events" detected." */
  TU_Bln361095dataCarrierSMARTattrDef(
    /**Evt=EVenT: http://www.allacronyms.com/event/abbreviated
     * Cnt=CouNT: http://www.abbreviations.com/abbreviation/Count */
    FreeFallEvtCnt) = 254
};

TU_Bln361095dataCarrierSMARTattrNmSpcEnd

#endif///include guard
