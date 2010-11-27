/*
 * IsUSBdrive.cpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else g++ compilation errors like
// "error: `GetDriveTypeW' cannot be used as a function"
//For indirectly declaring CreateFile(...), DeviceIoControl(...),
// GetDriveType(...)
#include <windows.h>
#include <Controller/character_string/stdtstr.hpp> //class std::tstring
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <tchar.h> //_T(...)
#include <windef.h> //BOOL
//#include <string> //class std::string
#include "GetDisksProperty.hpp" //GetDisksProperty(...)
#include "HardwareAccess.hpp" //PSTORAGE_DEVICE_DESCRIPTOR
//#include <winbase.h>

/****************************************************************************
*    PURPOSE:  liefert zurück, ob ein Pfad auf einem über USB
    angeschlossenen Laufwerk
****************************************************************************/
BOOL IsUSBDrive( const //CString
  std::tstring & cr_stdtstrFullPathOfDir
  )
{
  BOOL bIsUSBStickDrive = FALSE;
  //DWORD     drive, drivetype;
  HANDLE      hDevice;
  PSTORAGE_DEVICE_DESCRIPTOR pDevDesc;

#ifdef _DEBUG
  TRACE("GetDriveType(strFullPathOfDir.Left(2)): %u\n",
    GetDriveType(//strFullPathOfDir.Left(2)
    cr_stdtstrFullPathOfDir.substr()
      )
    );
#endif
  if( //strFullPathOfDir.GetLength() > 1
    cr_stdtstrFullPathOfDir.length() > 1
    )
    switch ( ::GetDriveType( cr_stdtstrFullPathOfDir.//Left(2)
              substr(0,2).c_str()
             )
      )
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
        //drivetype = DRVREMOVE;
        //Syntax von Laufwerksbezeichnungen für "CreateFile":
        // "\\.\Laufwerksbuchstabe:"
        std::tstring stdtstrCreateFilePath = std::tstring( _T("\\\\.\\") ) +
          cr_stdtstrFullPathOfDir.substr(
            0, //pos
            2 //size
            ) ;
        hDevice = ::CreateFile(//GetDriveType(
//          CString("\\\\.\\") +
//          strFullPathOfDir.Left(2),
          stdtstrCreateFilePath.c_str() ,
          //Specifies device query access to the object. An application can
          //query device attributes without accessing the device.
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
          pDevDesc = (PSTORAGE_DEVICE_DESCRIPTOR) new
            BYTE[ sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1 ];
          pDevDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;

          if( ::GetDisksProperty(hDevice, pDevDesc) )
          {
            WORD wRun = 0 ;
            TRACE("Rohdaten:");
            for( ; wRun < 512 + sizeof(STORAGE_DEVICE_DESCRIPTOR) ; ++ wRun )
              TRACE("%c",*((BYTE*)(pDevDesc)+wRun));//(BYTE)(pDevDesc+42)
            TRACE("\n");
            TRACE("S/N-Offset:%u,S/N:",pDevDesc->SerialNumberOffset);
            for( wRun = //TODO SerialNumberOffset may exceed WORD value range
              (WORD) pDevDesc->SerialNumberOffset;
              wRun < 512 + sizeof(STORAGE_DEVICE_DESCRIPTOR); ++ wRun
              )
              TRACE("%c(%d)", * ( ( BYTE * ) (pDevDesc) + wRun),
                * ( (BYTE * ) (pDevDesc) + wRun ) );//(BYTE)(pDevDesc+42)
            TRACE("\n");
            TRACE("ProductIdOffset:%u,ProductIdOffset:",
              pDevDesc->ProductIdOffset);
            for( wRun = //TODO ProductIdOffset may exceed WORD value range
              (WORD) pDevDesc->ProductIdOffset ;
              wRun < 512 + sizeof(STORAGE_DEVICE_DESCRIPTOR) ; ++ wRun
              )
              TRACE("%c(%d)", * ( (BYTE * ) (pDevDesc) + wRun),
                * ( (BYTE * ) ( pDevDesc) + wRun ) );//(BYTE)(pDevDesc+42)
            TRACE("\n");
            if( pDevDesc->BusType ==
               //from "enum _STORAGE_BUS_TYPE"
               BusTypeUsb )
            {
              bIsUSBStickDrive = TRUE;
            }
#ifdef _DEBUG
            TRACE("pDevDesc->SerialNumberOffset\n");
  /*ULONG  Version;
  ULONG  Size;
  UCHAR  DeviceType;
  UCHAR  DeviceTypeModifier;
  BOOLEAN  RemovableMedia;
  BOOLEAN  CommandQueueing;
  ULONG  VendorIdOffset;
  ULONG  ProductIdOffset;
  ULONG  ProductRevisionOffset;
  ULONG  SerialNumberOffset;
  STORAGE_BUS_TYPE  BusType;
  ULONG  RawPropertiesLength;
  UCHAR  RawDeviceProperties[1];*/

#endif
          }
          delete pDevDesc;
          ::CloseHandle( hDevice );
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
  return bIsUSBStickDrive;
}
