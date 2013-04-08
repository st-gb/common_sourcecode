/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */

//assign a second value to a value beginning from pos "offset":
//1st: set all

//!000010101 (value to insert)
//=111101010 (negation)
//&101010110 (orig value)
//=101000010

// 000010101 (value to insert)
//&111101010 (negation)

//    111101010 (negation of value to insert)
//xor 101010110 (original value)
//=   010111100 (Differenzen zwischen negation of value to insert und original value)

//    000010101 (value to insert)
//xor 101010110 (original value)
//=   101000011 (Differenzen zwischen value to insert und original value)
//xor 101010110 (original value)
//=   000010101

//    101010110 (original value)
//nand101000011 (Differenzen zwischen value to insert und original value)
//=   010111101
//&   101010110 (original value)
//=   000010100
//&   101010110 (original value)
//=   000010100

//    000010101 (value to insert)
//&   101000011 (Differenzen zwischen value to insert und original value)
//=   000000001

// 000010101 (value to insert)
//&101010110 (orig value)
//=000010100
//---
//!000010100
//---------
//=111101011
//&101010110 (orig value)
//=101000010
#define SET_DWORD_VALUE(orig_value,offset,new_value) ( ( orig_value & \
  new_value | 0xFFFFFFFF ) << offset)

//Bitmaske erstellen: ( 2 << bit_length ) = 2^bit_length, e.g. 2 << 3 = 2^3 = 8 = 1000bin
//( 2 << bit_length ) - 1 = 8 - 1 = 7 = 111bin
//Bitmaske an die richtige Stelle schieben: "( ( 2 << bit_length ) - 1 ) << offset" : 
// if offset = 3: "111000bin"
//negate bitmask: "! ( ( ( 2 << bit_length ) - 1 ) << offset )": 
//e.g. "111111111111111111111111000111bin"
//"value_to_insert & ( 2 << bit_length )": ensure it is limited to "bit_length"
#define INSERT_INTO_DWORD_VALUE(orig_value,offset,bit_length,value_to_insert) \
  ( \
    orig_value & \
    ( \
      ! ( ( ( 2 << bit_length ) - 1 ) << offset ) \
    ) | \
    ( value_to_insert & ( ( 2 << bit_length ) - 1 ) \
      << offset \
    ) \
  )
