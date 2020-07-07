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

//TODO move to common_sourcecode
/** See https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes */
enum SMARTattributeNames 
{
  /**https://de.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology#.C3.9Cbliche_Parameter :
   "Laufleistung in Stunden oder Sekunden (inklusive Standby)
   Deutet auf Abnutzung hin, sagt aber nichts über Nutzungsumstände in dieser Zeit aus.
   Bei einigen Modellen von Maxtor, z. B. bei der Maxtor DiamondMax 10 6L250S0 
   * sind das Minuten." */
  PowerOnTime = 9,
  TempDiffOrAirflowTemp=190,
  DevTemp = 194,
  /**https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
    * "Time spent during the positioning of the drive heads. Some Fujitsu 
   *  drives report the count of link resets during a data transfer. */
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
  TotalDataRead = 242///"Data" because unit is not always "LBAs"
};

#ifdef __cplusplus
} //namespace SMARTattributeNames
}
#endif

#endif /* SMARTATTRIBUTENAMES_H */
