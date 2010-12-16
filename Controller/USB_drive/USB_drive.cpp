/*
 * USB_drive.cpp
 *
 *  Created on: Nov 8, 2010
 *      Author: Stefan
 */
#include "USB_drive.hpp"

bool DirToBeCopyIsDeclaredAsUSBDrive(const CString & strDirToBeCopy)
{
  bool bDirToBeCopyDeclaredAsUSBDrive = false;
  if(strDirToBeCopy.Left(3).CompareNoCase("USB") == 0 )
    bDirToBeCopyDeclaredAsUSBDrive = true;
  return bDirToBeCopyDeclaredAsUSBDrive;
}

bool DirToBeCopyIsDeclaredAsUSBStick(const CString & strDirToBeCopy)
{
  bool bDirToBeCopyDeclaredAsUSBStick = false;
  if(strDirToBeCopy.Left(9).CompareNoCase("USB-Stick") == 0
    || strDirToBeCopy.Left(8).CompareNoCase("USBStick") == 0 )
    bDirToBeCopyDeclaredAsUSBStick = true;
  return bDirToBeCopyDeclaredAsUSBStick;
}

CString RemoveUSBLabel(const CString & strDir)
{
  CString strBack;
  if(strDir.Left(3).CompareNoCase("USB") == 0 )
    strBack=strDir.Right(strDir.GetLength() - 3 );
  return strBack;
}

CString RemoveUSBStickLabel(const CString & strDir)
{
  CString strBack;
  if(strDir.Left(9).CompareNoCase("USB-Stick") == 0 )
    strBack=strDir.Right(strDir.GetLength() - 9 );
  if(strDir.Left(8).CompareNoCase("USBStick") == 0 )
    strBack=strDir.Right(strDir.GetLength() - 8 );
  return strBack;
}
