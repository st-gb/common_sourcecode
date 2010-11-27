/*
 * UnmountVolume.cpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else g++ compilation errors like
// "error: `GetDriveTypeW' cannot be used as a function"
//For indirectly declaring CreateFile(...), DeviceIoControl(...)
#include <windows.h>
#include <Controller/character_string/stdtstr.hpp> //class std::tstring
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <tchar.h> //_T(...)
#include <WinIoCtl.h> //FSCTL_DISMOUNT_VOLUME (etc.)

bool UnmountVolume(//CString
  const std::tstring & cr_stdtstrDriveName //,
//  I_UserInterface * p_userinterface
  )
{
  bool bSuccessfullyUnmunted = false ;
  HANDLE hDrive;
  std::tstring stdtstrCreateFilePath = std::tstring( _T("\\\\.\\") ) +
    cr_stdtstrDriveName ;
  //Lock the volume.(to ensure dismount)
  //In the preceding string, X is a hard-drive partition letter,
  //  floppy disk drive, or CD-ROM drive. The application must
  //  also specify the FILE_SHARE_READ and FILE_SHARE_WRITE
  //  flags in the dwShareMode parameter of CreateFile.
  hDrive = ::CreateFile(
    //(LPCTSTR) ( //CString("\\\\.\\")
    stdtstrCreateFilePath.c_str() ,
    //dwDesiredAccess
    0//GENERIC_READ|GENERIC_WRITE
    ,
    //The application must also specify the FILE_SHARE_READ
    //and FILE_SHARE_WRITE flags in the dwShareMode parameter
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL,//lpSecurityAttributes
    OPEN_EXISTING, NULL,//dwFlagsAndAttributes
    NULL//hTemplateFile
    );

  if (hDrive != INVALID_HANDLE_VALUE)
  {
    DWORD dwBytesReturned;
    if(
      ::DeviceIoControl(
        hDrive,
        FSCTL_LOCK_VOLUME,
        NULL,
        0,
        NULL,
        0,
        & dwBytesReturned,
        (LPOVERLAPPED) NULL
        )
      )
      TRACE("locked\n");
    else
      TRACE("!locked: %s\n" , ::GetLastErrorMessageString(
        ::GetLastError())
        );
    if(
//      DeviceIoControl(
//      hDrive,            // handle to volume
//      FSCTL_DISMOUNT_VOLUME,       // dwIoControlCode
//      NULL,// lpInBuffer is not used; must be NULL
//      0,// nInBufferSize is not used; must be zero
//      NULL,// lpOutBuffer is not used; must be NULL
//      0,// nOutBufferSize is not used
//      //If lpOverlapped is NULL (nonoverlapped I/O),
//      //lpBytesReturned is used internally and cannot be NULL.
//      &dwBytesReturned,   // number of bytes returned
//      //If hDevice was opened without specifying the
//      //FILE_FLAG_OVERLAPPED flag, this parameter is ignored
//      //and the DeviceIoControl function does not return
//      //until the operation has been completed, or until an error occurs.
//      NULL  // OVERLAPPED structure
//      )
        ::DeviceIoControl(
         hDrive,
         FSCTL_DISMOUNT_VOLUME,
         NULL,
         0,
         NULL,
         0,
         & dwBytesReturned,
         NULL
         )
      )
      //AfxMessageBox("Sie können das LW jetzt entfernen");
      //p_userinterface->ShowMessage("Sie koennen das Laufwerk jetzt "
      // "entfernen");
      bSuccessfullyUnmunted = true ;
    else
      TRACE("!dismounted: %s\n", ::GetLastErrorMessageString(
        ::GetLastError() )
        );
    if(
      ::DeviceIoControl(
        hDrive,
        IOCTL_STORAGE_MEDIA_REMOVAL,
        NULL,
        0,
        NULL,
        0,
        & dwBytesReturned,
        NULL
        )
      )
      TRACE("removed\n");
    else
      TRACE("!removed: %s\n", GetLastErrorMessageString( ::GetLastError() ) );
    ::CloseHandle(hDrive);
  }
  return bSuccessfullyUnmunted ;
}
