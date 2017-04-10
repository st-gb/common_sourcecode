#pragma once

#include <hardware/CPU/fastest_data_type.h>
//#include <Controller/character_string/ISO_8859_1.hpp>
#include <preprocessor_macros/bitmasks.h>

class UTF8string
{
public:
  UTF8string(const unsigned char * const pchArray, const unsigned sizeInBytes)
  {
    
  }
  
  /** see http://www.utf8-zeichentabelle.de/unicode-utf8-table.pl?number=1024&htmlent=1 
   *  The 2nd (and last) byte of a 2-byte UTF-8 sequence. */
  enum secondUTF8byte
  {
    Ae = 0x84,
    Oe = 0x96,
    Ue = 0x9c,
    ae = 0xa4,
    oe = 0xb6,
    ue = 0xbc
  };

  /** @param p_by: start of a multi-byte UTF-8 value. */
  static unsigned GetAsUnicode(const unsigned char * const p_by, unsigned & numUTF8bytes)
  {
//    unsigned numUTF8bytes = 0;
    numUTF8bytes = 0;
    unsigned unicode = 0;
    unsigned char firstByte = p_by[0];
    /**see http://de.wikipedia.org/wiki/UTF8#Kodierung :
     *  # of UTF-8 bytes equals the number of the first "1" bits */
    while( (firstByte & 128) == 128 )
    {
      firstByte <<= 1;
      numUTF8bytes ++;
    }
    firstByte >>= numUTF8bytes;
    unicode = firstByte;
    unsigned char currentByte;
    unsigned lowmost6BitsOfCurrentByte;
    for( unsigned utf8byteIndex = 1; utf8byteIndex < numUTF8bytes; ++ utf8byteIndex)
    {
      currentByte = p_by[utf8byteIndex];
      if( currentByte > 128 )
      {
        unicode <<= 6;
        lowmost6BitsOfCurrentByte = currentByte & BITMASK_FOR_LOWMOST_6BIT;
        unicode |= lowmost6BitsOfCurrentByte;
      }
    }
//    numBytes = 
//    do
//    pby[
    return unicode;
  }

  static std::string GetAsISO_8859_1StdString(
    const unsigned char * const pchArray, 
    const unsigned sizeInBytes)
  {
    std::string std_strReturn;
    char * const p_ch = new char[sizeInBytes /*1 string terminating NULL char*/ 
      + 1];
    if( p_ch )
    {
      unsigned char currentByte;
      unsigned charIndex = 0;
      unsigned numUTF8bytes;
      char ch;
      for( fastestUnsignedDataType byteIndex = 0; byteIndex < sizeInBytes; ++ byteIndex)
      {
        currentByte = pchArray[byteIndex];
        if( currentByte < 0x7f )
        {
          p_ch[charIndex] = currentByte;
        }
        else
        {
//          ISO_8859_1::GetAsISO_8859_1char(/*pchArray + byteIndex*/);
          const unsigned unicodeChar = GetAsUnicode(pchArray + byteIndex, numUTF8bytes);
          byteIndex += numUTF8bytes - 1;
//          ch = ISO_8859_1::GetAsISO_8859_1char(unicodeChar);
          std_strReturn += /*ch*/ (char) unicodeChar;
        }
        ++ charIndex;
      }
      std_strReturn = std::string(p_ch, charIndex);
    }
    return std_strReturn;
  }
};
