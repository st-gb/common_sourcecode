#ifdef MS_COMPILER
  #include <windef.h> //for "BYTE" etc.
  #include "afx.h" //for TRACE()
#endif

#include <windows.h> //GetFileAttributes()
#include <string> //std::string

//#include "ErrorCodeFromGetLastErrorToString.h" //GetLastErrorMessageString()s
#ifndef _MSC_VER
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility;
#endif //#ifndef _MSC_VER
#include <preprocessor_macros/trace.h> //TRACE(...)
//#include <Controller/Sync_String.h>
//#include <global.h> //for TRACE(...)
#include <Windows/FileSystem/FileSystemAccess.hpp>
//#include "../UserInterface/userInterface.hpp"

//typedef MFC_Compatibility::CString Sync_String ;

#ifdef COMPILE_AS_STATIC_CLASS_ELEMENTS
//  DWORD FileSystemAccess::CreateMissingDirLevelsOfDirPath(
//  const std::string & strFullDirPath
//  , int & nIndexOfBackslashWhereErrorOccured
//  );
#endif

//diese Funktion funktioniert auch mit UNC-Namen
bool DirOrAnySuperDirExists(
  //as a copy, because it is modified within this function
  CString strPathOfDirToProof
//  std::string strPathOfDirToProof
//  Sync_String strPathOfDirToProof
  )
{
	bool bDirExists = false;
	DWORD dwFileAttributes;
	int nIndexOfLastBackslash = 0;
  TRACE("DirOrAnySuperDirExists(%s) Anfang\n",strPathOfDirToProof);
	do
	{
    TRACE("vor GetFileAttributes(%s) Anfang\n",strPathOfDirToProof);
		//GetFileAttributes liefert auch einen Wert <>0xFFFFFFFF,
		//wenn strPathOfDirToProof "\" ist--problematisch?
		if(
        ( dwFileAttributes = 
            ::GetFileAttributes( //(LPCTSTR) strPathOfDirToProof
//            ::GetFileAttributesA( //(LPCTSTR) strPathOfDirToProof
            strPathOfDirToProof.c_str()
            )
        ) != 0xFFFFFFFF//)
		//{
		//wenn die Funktion GetFileAttributes erfolgreich war
			//Es kann sein, dass ein Verzeichnis auf der Seite der
			//zu erhaltenden Synchronisation/Kopien noch NICHT
			//existiert! (z.B. lief dieses Programm NICHT die ganze
			//Zeit mit, Zugriffsrechte verweigert etc.)

			//wenn der Quellpfad ein Verzeichnis ist
			//if(
         && dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
       )
			{
				bDirExists = true;
				break;
			}
		//}
    //If not file attributes could be retrieved OR if attributes 
    //could be retrieved and nt a directory.
		else
		{
			nIndexOfLastBackslash = strPathOfDirToProof.
				ReverseFind('\\');
			//Bsp.: "C:\",UNC-Name "\\a"
			if( nIndexOfLastBackslash > 1 )
				//-1 if the character is not found.
				strPathOfDirToProof = strPathOfDirToProof.Left(
					nIndexOfLastBackslash);
		}
	}while( nIndexOfLastBackslash > 1 );
	return bDirExists;
}

bool DirExists( const CString & cr_stdstringFullPathOfDirToProof
//  const std::string & cr_stdstringFullPathOfDirToProof
  )
{
	bool bDirExists=false;
	DWORD dwFileAttributes;
  if( ( dwFileAttributes = //::GetFileAttributes( (LPCTSTR)
    ::GetFileAttributesA( (LPCSTR)
          cr_stdstringFullPathOfDirToProof)
      )
      != //0xFFFFFFFF
      INVALID_FILE_ATTRIBUTES
    )
  {
    //Wenn die Funktion GetFileAttributes erfolgreich war
		//es kann sein, dass ein Verzeichnis auf der Seite der
		//zu erhaltenden Synchronisation/Kopien noch NICHT
		//existiert! (z.B. lief dieses Programm NICHT die ganze
		//Zeit mit, Zugriffsrechte verweigert etc.)

		//Wenn der Quellpfad ein Verzeichnis ist.
		if( dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			bDirExists = true ;
		}
  }
  else
    TRACE("DirExists(const CString &) ::GetLastError():%s\n",
      ::GetLastErrorMessageString(::GetLastError()));
	return bDirExists;
}

bool DriveOfPathExists( const CString & cr_stdstringPathOfDirToProof
//  const std::string & cr_stdstringPathOfDirToProof
  )
{
	bool bDriveExists = false;
	if( cr_stdstringPathOfDirToProof.//GetLength()
	    length() > 2
	  )
	{
		DWORD dwFileAttributes;
		if( ( dwFileAttributes = //::GetFileAttributes( (LPCTSTR)
		      ::GetFileAttributesA( (LPCSTR)
            cr_stdstringPathOfDirToProof.Left(3)
//            substr(0,3)
          )
        ) != 0xFFFFFFFF
      )
		//wenn die Funktion GetFileAttributes erfolgreich war
		{
			//es kann sein, dass ein Verzeichnis auf der Seite der
			//zu erhaltenden Synchronisation/Kopien noch NICHT
			//existiert! (z.B. lief dieses Programm NICHT die ganze
			//Zeit mit, Zugriffsrechte verweigert etc.)

			//wenn der Quellpfad ein Verzeichnis ist
			if( dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				bDriveExists = true;
			}
		}
	}
	return bDriveExists;
}
