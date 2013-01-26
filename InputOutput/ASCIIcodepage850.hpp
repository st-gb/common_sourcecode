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
  //values from de.wikipedia.org/wiki/Codepage_850
  enum ASCIIcodepage850_chars
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
}

#endif /* ASCIICODEPAGE850_HPP_ */
