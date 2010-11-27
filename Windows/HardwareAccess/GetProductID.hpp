/*
 * GetProductID.hpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */

#ifndef GETPRODUCTID_HPP_
#define GETPRODUCTID_HPP_

#ifndef _MFC_VER
  //class MFC_Compatibility::CString
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif

bool GetProductID(
  BYTE byDriveNumberCorrespondigToDriveLetter,
  CString
  //std::string
    & rstrProductID
  );

#endif /* GETPRODUCTID_HPP_ */
