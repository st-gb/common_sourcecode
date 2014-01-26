/*
 * ASCIIcodepage850.hpp
 *
 *  Created on: 25.01.2013
 *      Author: Stefan
 */

#ifndef ASCIICODEPAGE850_HPP_
#define ASCIICODEPAGE850_HPP_

namespace ASCIIcodepage850
{
  /** @ brief Code page for West Europe
   * values from de.wikipedia.org/wiki/Codepage_850 */
  enum ASCIIcodepage850_HTML_codes
  {
    //"è" as in "Apr_è_s Ski";
    egrave = 0x8A,
    auml = 228, //"ae" (falls wieder anderer Zeichensatz)
    ouml = 246, //"oe" (falls wieder anderer Zeichensatz)
    uuml = 252, //"ue" (falls wieder anderer Zeichensatz)
    Auml = 196, //"Ae" (falls wieder anderer Zeichensatz)
    Ouml = 214, //"Oe" (falls wieder anderer Zeichensatz)
    Uuml = 220, //"Ue" (falls wieder anderer Zeichensatz)
    szlig = 223 //"sz" (falls wieder anderer Zeichensatz)
  };
  /** @ brief Code page for West Europe
   * values from de.wikipedia.org/wiki/Codepage_850
   * / http://de.wikipedia.org/wiki/ISO_8859-1 */
  enum ASCIIcodepage850_chars
  {
    ae = 228, //0xE4 "ae" (falls wieder anderer Zeichensatz)
    oe = 246, //0xF6 "oe" (falls wieder anderer Zeichensatz)
    ue = 252, //0xFC "ue" (falls wieder anderer Zeichensatz)
    Ae = 196, //0xC4 "Ae" (falls wieder anderer Zeichensatz)
    Oe = 214, //0xD6 "Oe" (falls wieder anderer Zeichensatz)
    Ue = 220, //0xDC "Ue" (falls wieder anderer Zeichensatz)
    sz = 223 //0xDF "sz" (falls wieder anderer Zeichensatz)
  };
}

#endif /* ASCIICODEPAGE850_HPP_ */
