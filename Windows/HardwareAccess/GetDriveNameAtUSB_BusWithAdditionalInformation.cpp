/*
 * GetDriveNameAtUSB_BusWithAdditionalInformation.cpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else g++ compilation errors like
// "error: `GetDriveTypeW' cannot be used as a function"
//For indirectly declaring CreateFile(...), DeviceIoControl(...)
#include <windows.h>
#include "GetDisksProperty.hpp" //GetDisksProperty(...)
#include "HardwareAccess.hpp" //PSTORAGE_DEVICE_DESCRIPTOR
#ifndef _MFC_VER
  //class MFC_Compatibility::CString
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif
//for GetCStringWithRemovedNullChars(...)
#include <Controller/character_string/MFC_Compatibility/\
GetCStringWithRemovedNullChars.hpp>
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <tchar.h> //_T()

CString GetDriveNameAtUSB_BusWithAdditionalInformation(
  const CString & strFullPathOfDir
  )
{
  CString strDriveNameAtUSB_BusWithAdditionalInformation;
  //DWORD     drive, drivetype;

#ifdef _DEBUG
  TRACE("GetDriveType(strFullPathOfDir.Left(2)): %u\n",
    GetDriveType(strFullPathOfDir.Left(2)));
#endif
  if(strFullPathOfDir.GetLength() > 1)
  {
    CString strDriveName;
    strDriveName = strFullPathOfDir.Left(2);
    switch ( ::GetDriveType(strDriveName.c_str() ) )
    {
      case 0:         // The drive type cannot be determined.
      case 1:         // The root directory does not exist.
        //drivetype = DRVUNKNOWN;
        break;
      case DRIVE_CDROM:   // The drive is a CD-ROM drive.
        break;
      //ein Acer UFD USB-Stick wurde zum Beispiel als DRIVE_FIXED
      //gemeldet!
      case DRIVE_FIXED:
      //ansonsten werden USB-Sticks oft als entfernbar gemeldet
      case DRIVE_REMOVABLE: // The drive can be removed from the drive.
      {
        HANDLE hDevice;
        //drivetype = DRVREMOVE;
        //Syntax von Laufwerksbezeichnungen für "CreateFile":
        // "\\.\Laufwerksbuchstabe:"
        std::tstring stdtstrPath = CString( _T("\\\\.\\") ) + strDriveName ;
        hDevice = ::CreateFile(//GetDriveType(
          stdtstrPath.c_str() ,
          //Specifies device query access to the object. An application can query device attributes without accessing the device.
          0//GENERIC_READ
          ,
          FILE_SHARE_READ | FILE_SHARE_WRITE,
          NULL,
          OPEN_EXISTING,
          NULL,
          NULL
          );
        if (hDevice != INVALID_HANDLE_VALUE)
        {
          PSTORAGE_DEVICE_DESCRIPTOR pDevDesc;
          pDevDesc = (PSTORAGE_DEVICE_DESCRIPTOR) new
            BYTE[ sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1 ];

          pDevDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;

          if( GetDisksProperty(hDevice, pDevDesc) )
          {
            TRACE("Rohdaten:");
            //for(WORD wRun=0;wRun<512+sizeof(STORAGE_DEVICE_DESCRIPTOR);++wRun)
            //  TRACE("%c",*((BYTE*)(pDevDesc)+wRun));//(BYTE)(pDevDesc+42)
            //TRACE("\n");
            //TRACE("S/N-Offset:%u,S/N:",pDevDesc->SerialNumberOffset);
            TRACE("\n");
            if(pDevDesc->BusType == BusTypeUsb )
            {
              //bIsUSBStickDrive=TRUE;
              strDriveNameAtUSB_BusWithAdditionalInformation=
                strDriveName;
              //for(wRun=pDevDesc->SerialNumberOffset;wRun<512+
              //  sizeof(STORAGE_DEVICE_DESCRIPTOR);++wRun)
              //  TRACE("%c(%d)",*((BYTE*)(pDevDesc)+wRun),
              //  *((BYTE*)(pDevDesc)+wRun));//(BYTE)(pDevDesc+42)
              TRACE("\n");
              if(pDevDesc->VendorIdOffset != 0)
              {
                WORD wEndIndex =
                  //TODO Size may exceed WORD value range
                  (WORD)pDevDesc->Size;
                strDriveNameAtUSB_BusWithAdditionalInformation +=
                  //CString((char*)(pDevDesc)+pDevDesc->VendorIdOffset,
                  //pDevDesc->Size-pDevDesc->VendorIdOffset);
                  GetCStringWithRemovedNullChars(
                    (char * )(pDevDesc) + pDevDesc->VendorIdOffset,
                    //TODO VendorIdOffset may exceed WORD value range
                    (WORD)(pDevDesc->Size - pDevDesc->VendorIdOffset) );
              }
              else
              if(pDevDesc->ProductIdOffset != 0 )
              {
                WORD wEndIndex=//TODO Size may exceed WORD value range
                  (WORD)pDevDesc->Size;
                strDriveNameAtUSB_BusWithAdditionalInformation+=
                  //CString((char*)(pDevDesc)+pDevDesc->ProductIdOffset,
                  //pDevDesc->Size-pDevDesc->ProductIdOffset);
                  GetCStringWithRemovedNullChars(
                    (char*)(pDevDesc)+pDevDesc->ProductIdOffset,
                    //TODO ProductIdOffset may exceed WORD value range
                    (WORD)(pDevDesc->Size-pDevDesc->ProductIdOffset) );
              }
              else
              if(pDevDesc->SerialNumberOffset!=0)
              {
                WORD wEndIndex=//TODO Size may exceed WORD value range
                  (WORD) pDevDesc->Size;
                strDriveNameAtUSB_BusWithAdditionalInformation +=
                  //CString((char*)(pDevDesc)+pDevDesc->SerialNumberOffset,
                  //pDevDesc->Size-pDevDesc->SerialNumberOffset);
                  GetCStringWithRemovedNullChars(
                    (char * )( pDevDesc) + pDevDesc->SerialNumberOffset,
                    //TODO ProductIdOffset may exceed WORD value range
                    (WORD) (pDevDesc->Size-pDevDesc->ProductIdOffset) );
              }
            }
#ifdef _DEBUG
            TRACE("pDevDesc->SerialNumberOffset\n");

#endif
          }
          delete pDevDesc;
          CloseHandle(hDevice);
        }
      }
        break;
        //break;
      case DRIVE_REMOTE:    // The drive is a remote (network) drive.
        //drivetype = DRVREMOTE;
        //szMoveDiskName[k] = chFirstDriveFromMask(temp);
        //szMoveDiskName[0]=k;
        //k++;
        break;
      case DRIVE_RAMDISK:   // The drive is a RAM disk.
        //drivetype = DRVRAM;
        break;
    }
  }
  return strDriveNameAtUSB_BusWithAdditionalInformation;
}
