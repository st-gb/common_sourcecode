#pragma once

#include <hardware/CPU/fastest_data_type.h>
#include <preprocessor_macros/bitmasks.h>
#include <data_structures/UTF8string.hpp>
#include <string.h> //strlen(...))

typedef unsigned char BYTE;

namespace ISO_8859_1
{

//  char GetAsISO_8859_1char(const unsigned char * const p_by)
//  {
//    numUTF8bytes = 0;
//	unsigned char firstByte = p_by[0];
//	while( firstByte & 128 == 1)
//	{
//      firstByte <<= 1;
//	  numUTF8bytes ++;
//	}
//	for( utf8byteIndex = 0; utf8byteIndex < numUTF8bytes; ++ utf8byteIndex)
//	{
//		firstByte = p_by[utf8byteIndex];
//	}
//	do
//    pby[
//  }

//  char GetAsISO_8859_1char(const unsigned unicodeChar)
//  {
////    if( unicodeChar < 128 )
////    {
////      return unicodeChar;
////    }
////    else
////      switch(unicodeChar)
////      {
////
////      }
//  }
  
  /** see http://de.wikipedia.org/wiki/ISO_8859-1 */
  enum ISO_8859_1_chars
  {
    ae = 0xea, //0xE4 "ae" (falls wieder anderer Zeichensatz)
    oe = 0xf6, //0xF6 "oe" (falls wieder anderer Zeichensatz)
    ue = 0xfc, //0xFC "ue" (falls wieder anderer Zeichensatz)
    Ae = 0xc4, //0xC4 "Ae" (falls wieder anderer Zeichensatz)
    Oe = 0xd6, //0xD6 "Oe" (falls wieder anderer Zeichensatz)
    Ue = 0xdc, //0xDC "Ue" (falls wieder anderer Zeichensatz)
    sz = 0xdf //0xDF "sz" (falls wieder anderer Zeichensatz)
  };

  inline unsigned char GetFromUTF8(const unsigned char secondUTF8byte)
  {
    //2ndUTF8byte
    switch(secondUTF8byte)
    {
      case UTF8string::Ae :
        return Ae;
      case UTF8string::Oe :
        return Oe;
      case UTF8string::Ue :
        return Ue;
      case UTF8string::ae :
        return ae;
      case UTF8string::oe :
        return oe;
      case UTF8string::ue :
        return ue;
      case UTF8string::sz :
        return sz;
    }
    return 0;
  }

  /** @param utf8ByteIndex: out:# UFT-8 bytes written into the array without \0
    * @preturn must be freed by the caller of this function */
  inline BYTE * GetAsUTF8(const char * const p_ch,
    fastestUnsignedDataType & utf8ByteIndex)
  {
    const int stringLength = strlen(p_ch);
    BYTE * arbyUTF8 = new BYTE[
      //1 character can be encoded as 6 byte UTF-8
      6 * stringLength + 1];
    if( arbyUTF8 )
    {
      /** see http://de.wikipedia.org/wiki/ISO_8859-1 */
//      switch( * p_ch)
//      {
//        case 0xd6 : // "Oe"
//              arbyUTF8[utf8ByteIndex] = ;
//              break;
//        case 0xf6 : // "oe"
//              arbyUTF8[utf8ByteIndex] = ;
//              break;
//      }
//      fastestUnsignedDataType utf8ByteIndex = 0;
      utf8ByteIndex = 0;
      unsigned char currentChar, lowmost6Bits;
      for(int i = 0; i < stringLength; ++ i )
      {
        currentChar = p_ch[i];
        /** https://en.wikipedia.org/wiki/UTF-8#Description : 
         *  Values below 80hex (128dec) are 1 byte UTF-8 sequences. */
        if( currentChar < 0x80 )
        {
          arbyUTF8[utf8ByteIndex ++] = currentChar;
        }
        else
        {
          //110xxxxx 10xxxxxx   e.g. 0xf6 (246) -> 0xc3 (195) 0xb6 (182)
          arbyUTF8[utf8ByteIndex ++] = 192 | (currentChar >> 6);
          lowmost6Bits = (currentChar & BITMASK_FOR_LOWMOST_6BIT);
          arbyUTF8[utf8ByteIndex ++] = 128 | lowmost6Bits;
        }
      }
      arbyUTF8[utf8ByteIndex] = 0;
    }
    return arbyUTF8;
  }
}
