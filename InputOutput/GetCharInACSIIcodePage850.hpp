#pragma once

#include "ASCIIcodepage850.hpp" //ASCIIcodepage850


namespace UTF8byteSequence
{
  enum bytePos { oneByteUTF8Char, none, last, insideUTF8sequence};

  bool IsByteOfMultiByteUTF8sequence(
    const unsigned char ch
    )
  {
    /** multi-byte UTF-8 character bytes are always > 127 */
    if( ch < 128 ) /** 1-byte UTF-8 sequence */
      return false;
    return true;
  }

  /** @param currentBytePosWithinUTF8sequence: 0-based index */
  enum bytePos IsByteOfUTF8sequence(
    const unsigned char * UTF8sequenceBegin,
    const unsigned currentBytePosWithinUTF8sequence)
  {
    if( UTF8sequenceBegin[0] < 128 )
      return oneByteUTF8Char;
    else
    {
      const unsigned char firstByte = UTF8sequenceBegin[0];
      unsigned numBitsToShift = 7;
      unsigned numUTF8Bytes = 0;
      /** see http://en.wikipedia.org/wiki/UTF-8#Description
       *  1st UTF-8 byte in binary:
       *  110....  -> 1 byte follows (2 bytes overall)
      *   1110...  ->    */
      while( ( ( firstByte >> numBitsToShift ) & 1 ) == 1)
      {
        ++ numUTF8Bytes;
        numBitsToShift --;
      }
      if( UTF8sequenceBegin[currentBytePosWithinUTF8sequence] > 127 &&
          numUTF8Bytes > currentBytePosWithinUTF8sequence )
        return insideUTF8sequence;
    }
    return none;
  }
}

/** @param ch: 2nd byte of 2 byte UTF-8 sequence */
//TODO move to namespace UTF8byteSequence
inline char GetCharInASCIIcodePage850(const int ch)
{
  switch (ch)
  {
  //case 195: //11000011bin
  //  break;
  //see http://www.utf8-zeichentabelle.de/unicode-utf8-table.pl?number=1024&htmlent=1
  case 164: //10100100bin
    return ASCIIcodepage850::ae /*'�'  "c3 a4" in UTF-8 */;
  case 0xb6:
    return ASCIIcodepage850::oe ; //'�';
  case 0xbc:
    return ASCIIcodepage850::ue ;//'�';
  case 0x9f:
    return ASCIIcodepage850::sz ;//'�' c3 9f ;
  case 0x84:
    return ASCIIcodepage850::Ae; //'�' c3 84 in UTF-8 ;
  case 0x96:
    return ASCIIcodepage850::Oe; //'�' c3 96 ;
  case 0x9c:
    return ASCIIcodepage850::Ue; //'�' c3 9c ;
  }
  return 0;
}
