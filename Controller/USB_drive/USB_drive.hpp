/*
 * USB_drive.hpp
 *
 *  Created on: Nov 8, 2010
 *      Author: Stefan
 */

#ifndef USB_DRIVE_HPP_
#define USB_DRIVE_HPP_

#ifndef _MSC_VER
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility;
#endif

bool DirToBeCopyIsDeclaredAsUSBStick(const CString & strDirToBeCopy);
bool DirToBeCopyIsDeclaredAsUSBDrive(const CString & strDirToBeCopy);

CString RemoveUSBStickLabel(const CString & strDir);
CString RemoveUSBLabel(const CString & strDir);

#endif /* USB_DRIVE_HPP_ */
