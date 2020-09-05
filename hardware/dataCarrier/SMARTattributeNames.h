/** File: SMARTattributeNames.h
 * Author: Stefan Gebauer, M.Sc. Comp. Sc./Informatik (TU Berlin)
 * Created on 2. Januar 2017, 23:36 */

#ifndef SMARTATTRIBUTENAMES_H
#define SMARTATTRIBUTENAMES_H

#ifdef __cplusplus
namespace SMARTattributeNames
{
extern "C" {
#endif

/** See https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes */
enum SMARTattributeNames
{
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#%C3%9Cbliche_Parameter
   * : "Nicht korrigierbare Fehler beim Lesen von der Festplatte, führt zum 
   * erneuten Einlesen. Deutet auf Problem mit der Plattenoberfläche hin."*/
  ReadErrorRate = 1,
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#%C3%9Cbliche_Parameter
   * : "Anzahl der verbrauchten Reservesektoren."*/
  ReallocSectorsCnt = 5,
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#.C3.9Cbliche_Parameter
   * : "-Laufleistung in Stunden oder Sekunden (inklusive Standby)
   * -Deutet auf Abnutzung hin, sagt aber nichts über Nutzungsumstände in dieser
   *   Zeit aus.
   * -Bei einigen Modellen von Maxtor, z. B. bei der Maxtor DiamondMax 10 6L250S0 
   *  sind das Minuten." */
  PowerOnTime = 9,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   *  "Count of retry of spin start attempts." */
  SpinUpRetryCnt = 10,
  PwrCycleCnt = 12,
  /** https://media.kingston.com/support/downloads/MKP_306_SMART_attribute.pdf
   * Unit can be determined by comparing to data written by OS?/
   * by getting the block numbers used when written (see "blktrace"--columns
   *  "start block" & "number of blocks" when write events) 
   *  https://git.kernel.dk/?p=blktrace.git;a=blob;f=blkparse_fmt.c;h=df2f6ce2148a473e20f5cd9afd381f0021bfd42d;hb=HEAD :
   *  is in "char *act" of "process_default" called from process_fmt 
     handle_notify 
    https://docs.huihoo.com/doxygen/linux/kernel/3.7/uapi_2linux_2blktrace__api_8h_source.html 
   https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwiGlt3f-c_qAhWPYsAKHZvXC7AQFjAFegQIBxAB&url=https%3A%2F%2Fcodesearch.isocpp.org%2Factcd19%2Fmain%2Fb%2Fblktrace%2Fblktrace_1.2.0-5%2Fblkiomon.c&usg=AOvVaw1nOLy95Q6Y-ixpgB8Krv1o */
  GiB_Erased = 100,
  SSDprogFailCnt = 171,
  SSDeraseFailCnt = 172,
  PwrLossProtectionFailure = 175,
  EraseFailCnt = 176,
  EndToEndError = 184,
  ReportedUncorrError = 187,
  CmdTimeout = 188,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "[...] recording head is flying outside its normal operating range [...]"*/
  HighFlyWrites = 189,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "Value is equal to (100-temp. °C), [...]
   * However, some older drives may instead report raw Temperature
   * (identical to 0xC2) or Temperature minus 50 here." */
  TempDiffOrAirflowTemp=190,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "The count of errors resulting from externally induced shock and
   *  vibration." */
  G_senseErrorRate = 191,
  DevTemp = 194,
  HW_ECC_Recovered = 195,
  ReallocEvtCnt = 196,
  CurrPendSecCnt = 197,
  UncorrSecCnt = 198,
  UDMA_CRCerrorCnt = 199,
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes
   * "A recording of shock encountered during write operations."*/
  ShockDuringWrite = 212,
  AvgEraseCntAndMaxEraseCnt = 234,
  /**https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "Time spent during the positioning of the drive heads. Some Fujitsu 
   *  drives report the count of link resets during a data transfer. 
   * Seen for a model "ST9500420AS" firmware "0003SDM1":only the lowmost (>=2)
   * bytes are relevant. The 2 highmost bytes changed fastly, unknown meaning.*/
  HeadFlyingHours = 240,
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
  TotalDataWritten = 241,///"Data" because unit is not always "LBA"
  TotalDataRead = 242,///"Data" because unit is not always "LBAs"
  /** https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
   * "Count of "Free Fall Events" detected." */
  FreeFallEvtCnt = 254
};

#ifdef __cplusplus
} //namespace SMARTattributeNames
}
#endif

#endif /* SMARTATTRIBUTENAMES_H */
