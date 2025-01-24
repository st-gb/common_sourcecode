/**(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095) */

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
/**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=Berlin: http://www.acronymfinder.com/Berlin-(Bln).html 
 * Typ=TYPe:
 * Uint=Unsigned INTeger */\
 !defined TU_Bln361095cmnSrc__dataType__bigUnit__boostMultiPrecArithmLib_h
  #define TU_Bln361095cmnSrc__dataType__bigUnit__boostMultiPrecArithmLib_h

///C(++) standard header files:
 #include <strstream>///class std::ostringstream

///Boost (working with version 1.8.1) header files:
 //https://www.boost.org/doc/libs/1_77_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html
 #include <boost/multiprecision/cpp_int.hpp>///boost::multiprecision::uint128_t
//#include "D:\Boost1.81.0\boost_1_81_0/boost/multiprecision/cpp_int.hpp"

///Stefan Gebauer's(TU Berlin matricul.numb.361095) ~ "cmnSrc" repository files:
 #include "bigUint_ID_prefix.h"//TU_Bln361095Uint16BtypDef()

 //TODO replace preprocessor macros with inline functions?!
typedef boost::multiprecision::uint128_t TU_Bln361095uInt16Btyp;
 typedef boost::multiprecision::uint128_t TU_Bln361095_16BuIntTyp;
 typedef TU_Bln361095uInt16Btyp TU_Bln361095_16B_uIntTyp;

#define TU_Bln361095Uint16BtypDecl(identifier) TU_Bln361095uInt16Btyp identifier
#define TU_Bln361095Uint16BtypRef(identifier) identifier

//TU_Bln361095_16B_uIntNmSpcBgn
//namespace TU_Bln361095 {
//  namespace _16B_uInt{

TU_Bln361095_16B_uIntNmSpcBgn

typedef /*TU_Bln361095_16B_uIntTyp*/ boost::multiprecision::uint128_t Typ;
//}

TU_Bln361095frcInln void //TU_Bln361095_16B_uIntAssign
 //TU_Bln361095_16B_uIntAssign
 Assign(
  TU_Bln361095::_16B_uInt::Typ & copy,
  const /*TU_Bln361095::_16B_uInt::*/Typ & origVal)
{
  copy.assign(origVal);/*num1 = num2*/
}

TU_Bln361095frcInln TU_Bln361095::_16B_uInt::Typ //TU_Bln361095_16B_uIntDiv
 // TU_Bln361095_16B_uIntDef(Div)
  Div
  (
  const TU_Bln361095::_16B_uInt::Typ & lftNum,
  const TU_Bln361095::_16B_uInt::Typ & rghtNum
  )
{
  return lftNum/rghtNum;
}

/** @brief
 *  @return  */
TU_Bln361095frcInln bool
  ///Equl=EQUaL
  //TU_Bln361095_16B_uIntIsEqul
  IsEqul(
  const TU_Bln361095_16B_uIntTyp & num1, const TU_Bln361095_16B_uIntTyp & num2)
{
  ///Compare returns 0 if equal
  return num1.compare(num2) == 0;
}

TU_Bln361095frcInln bool //TU_Bln361095_16B_uInt
  IsGreater(
  const TU_Bln361095_16B_uIntTyp & lftNum,
  const TU_Bln361095_16B_uIntTyp & rghtNum)
{
  return lftNum > rghtNum;
}

///@brief compares @see TU_Bln361095_16B_uIntTyp to unsigned int
TU_Bln361095frcInln bool //TU_Bln361095_16B_uInt
  IsGrtrThanUint(
  const TU_Bln361095_16B_uIntTyp & lftNum,
  const unsigned int & rghtNum)
{
  return lftNum > rghtNum;
}

///https://stackoverflow.com/questions/11544073/how-do-i-deal-with-the-max-macro-in-windows-h-colliding-with-max-in-std
#ifdef max
#undef max///Undefine to prevent compiler errors for using std::numeric_limits::max()
#endif

/** boost::multiprecision::uint128_t::get_max()*/
TU_Bln361095frcInln bool //TU_Bln361095_16B_uInt
  IsMax(
  const TU_Bln361095_16B_uIntTyp & number)
{
  return number == std::numeric_limits<boost::multiprecision::uint128_t>::max();
}

TU_Bln361095frcInln TU_Bln361095_16B_uIntTyp //TU_Bln361095_16B_uInt
  Minus(
  const TU_Bln361095_16B_uIntTyp & lftNum,
  const TU_Bln361095_16B_uIntTyp & rghtNum)
{
  return lftNum - rghtNum;
}

TU_Bln361095frcInln void //TU_Bln361095_16B_uInt
  Minus(
  const TU_Bln361095_16B_uIntTyp & lftNum,
  const TU_Bln361095_16B_uIntTyp & rghtNum,
  TU_Bln361095_16B_uIntTyp & rslt)
{
  rslt = lftNum - rghtNum;
}

/** boost::multiprecision::uint128_t::get_max()*/
TU_Bln361095frcInln void //TU_Bln361095_16B_uInt
  SetToMaxVal(
  TU_Bln361095_16B_uIntTyp & number)
{
  number = std::numeric_limits<boost::multiprecision::uint128_t>::max();
}

//static //inline
/** @param number 16 byte number to write as decimal number to character string
 *   \p numAsCharStrA.
 *  @param numAsCharStrA should have at least 40 array elements for the maximum
 *   number */
TU_Bln361095frcInln void
///DECimal NUMber TO CHARacter STRing
//TU_Bln361095_16B_uIntWriteAsDecNumToCharStr
//TU_Bln361095_16B_uIntDef(WriteAsDecNumToCharStr)
  WriteAsDecNumToCharStr
(
  const unsigned char number[16],
  char numAsCharStrA[])
{
  std::ostringstream stdoss;
  //UintB16TypImport
  ///https://stackoverflow.com/questions/52958235/how-do-i-convert-an-array-of-bytes-to-a-boostmultiprecisionuint128-t
  boost::multiprecision::cpp_int boostMultiPrecNum = 1;
  //boost::multiprecision::cpp_int::import_bits(boostMultiPrecNum, number, number+16);
  //memset(&boostMultiPrecNum, 0, 16);
  ///Write number encoded as byte array into "boost multiprecision" number.
  memcpy(&boostMultiPrecNum, number, (size_t)16);
  stdoss << boostMultiPrecNum;
  memcpy(numAsCharStrA/**destination*/, stdoss.str().c_str()/**source*/, 16);
}

TU_Bln361095_16B_uIntNmSpcEnd

#endif///Include guard