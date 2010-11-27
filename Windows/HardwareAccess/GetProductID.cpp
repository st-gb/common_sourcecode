/*
 * GetProductID.cpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else compilation errors.
#include <windows.h> //GetDriveType(...)
//#include <winbase.h> //GetDriveType(...)
#include "GetDisksProperty.hpp" //::GetDisksProperty(...)
#include "GetProductID.hpp" //class CString
#include "HardwareAccess.hpp" //PSTORAGE_DEVICE_DESCRIPTOR
#include <tchar.h> //_T(...)
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <Controller/character_string/MFC_Compatibility/\
GetCStringWithRemovedNullChars.hpp>

bool GetProductID(
  BYTE byDriveNumberCorrespondigToDriveLetter,
  CString & rstrProductID
//    std::string & rstrProductID
  )
{
  bool bSuccess = false;
  //CString strDriveNameAtUSB_BusWithAdditionalInformation;
  std::string strDriveNameAtUSB_BusWithAdditionalInformation;
  //DWORD     drive, drivetype;
  //The last element is for terminating 0 char.
  TCHAR ar_tchDriveName[3];
  ar_tchDriveName[0] = _T('A') + byDriveNumberCorrespondigToDriveLetter;
  ar_tchDriveName[1] = _T(':') ;
  ar_tchDriveName[2] = _T('\0') ;
  switch ( ::GetDriveType(ar_tchDriveName) )
  {
    case 0:         // The drive type cannot be determined.
    case 1:         // The root directory does not exist.
      //drivetype = DRVUNKNOWN;
      break;
    default:
      HANDLE hDevice;
      std::tstring stdtstrPath = std::tstring( _T("\\\\.\\") ) +
        ar_tchDriveName ;
      //Syntax von Laufwerksbezeichnungen für "CreateFile":
      // "\\.\Laufwerksbuchstabe:"
      hDevice = ::CreateFile(//GetDriveType(
        //CString("\\\\.\\") + archDriveName
        stdtstrPath.c_str() ,
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
      if ( hDevice != INVALID_HANDLE_VALUE )
      {
        PSTORAGE_DEVICE_DESCRIPTOR pDevDesc;
        pDevDesc = (PSTORAGE_DEVICE_DESCRIPTOR) new
          BYTE[ sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1 ];

        pDevDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;

        if( ::GetDisksProperty(hDevice, pDevDesc) )
        {
          TRACE("Rohdaten:");
          //for(WORD wRun=0;wRun<512+sizeof(STORAGE_DEVICE_DESCRIPTOR);++wRun)
          //  TRACE("%c",*((BYTE*)(pDevDesc)+wRun));//(BYTE)(pDevDesc+42)
          //TRACE("\n");
          //TRACE("S/N-Offset:%u,S/N:",pDevDesc->SerialNumberOffset);
          TRACE("\n");
          //for(wRun=pDevDesc->SerialNumberOffset;wRun<512+
          //  sizeof(STORAGE_DEVICE_DESCRIPTOR);++wRun)
          //  TRACE("%c(%d)",*((BYTE*)(pDevDesc)+wRun),
          //  *((BYTE*)(pDevDesc)+wRun));//(BYTE)(pDevDesc+42)
          TRACE("\n");
          //Wenn der erste Index der Produkt-ID zugewiesen wurde UND
          if( pDevDesc->ProductIdOffset != 0 &&
            //sich dieser Index niedriger als der letztmögliche Index ist
            pDevDesc->ProductIdOffset < pDevDesc->Size &&
            //UND die Produkt-Revision befindet sich indexmäßig höher als
            //die Produkt-ID UND...
            pDevDesc->ProductRevisionOffset > pDevDesc->ProductIdOffset
            &&
            //...sich dieser Index niedriger als der letztmögliche Index ist
            pDevDesc->ProductRevisionOffset < pDevDesc->Size
            )
          {
            rstrProductID =
              //CString((char*)(pDevDesc)+pDevDesc->ProductIdOffset,
              //pDevDesc->Size-pDevDesc->ProductIdOffset);
              ::GetCStringWithRemovedNullChars(
                (char * ) (pDevDesc) + pDevDesc->ProductIdOffset,
                //die Produkt-ID endet normalerweise DIREKT vor dem
                //Beginn der Produkt-Revision
                (WORD)(pDevDesc->ProductRevisionOffset -
                pDevDesc->ProductIdOffset )
                );
            //rstrProductID( (char*)(pDevDesc) + pDevDesc->ProductIdOffset,
            bSuccess = true ;
          }
#ifdef _DEBUG
          TRACE("pDevDesc->SerialNumberOffset\n");
#endif
        }
        delete pDevDesc;
        ::CloseHandle(hDevice);
      }
      break;
  }//switch (GetDriveType(archDriveName) )
  return bSuccess;
}//GetProductID(...)
