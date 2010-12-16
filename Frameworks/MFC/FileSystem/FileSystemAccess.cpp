#include "FileSystemAccess.hpp"
#include "afx.h" //for CFile::modeCreate etc.
#include <string> //for std::string
#include "UserInterface/UserInterface.hpp"
#include "ModelData/ProtocolFileData.hpp"

  bool FileSystemAccess::LoadProtocol(//const CString & rcstrFilePath
      const std::string & rcstdstrFilePath)
    {
#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
      mp_o2oapp->m_bFileOpenedSuccessfully = false;
#else
      mp_protocolfiledata->m_bFileOpenedSuccessfully = false;
#endif  //#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
      CFileException cfe;
      //Nonzero if the open was successful.
#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
      if(mp_o2oapp->m_fileFileAndDirChangeProtocol.Open(
#else
      if(mp_protocolfiledata->m_fileFileAndDirChangeProtocol.Open(
#endif  //#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
        //m_strRootPathForFileAndDirChangesProtocol+
        //pcDestinationDirAttributes->
        //m_strDestinationDirToReceiveChanges+
        //pcfilechange->m_strRelativePath,
        //rcstrFilePath,
        rcstdstrFilePath.c_str(),
        CFile::modeCreate|
        //Combine this value with modeCreate. If the file being created already exists, it is not truncated to 0 length. Thus the file is guaranteed to open, either as a newly created file or as an existing file.
        CFile::modeNoTruncate |
        CFile::modeReadWrite|CFile::shareDenyWrite//|
        //MFC Library Reference: "The system writes through any intermediate cache and goes directly to disk."
        //CFile::osWriteThrough|
        //MFC Library Reference: "The system opens a file with no system caching. This flag does not affect hard disk caching. When combined with FILE_FLAG_OVERLAPPED, the flag gives maximum asynchronous performance, because the I/O does not rely on the synchronous operations of the memory manager. However, some I/O operations take more time, because data is not being held in the cache. Also, the file metadata may still be cached. To flush the metadata to disk, use the FlushFileBuffers function.
        //An application must meet certain requirements when working with files that are opened with FILE_FLAG_NO_BUFFERING:
          //File access must begin at byte offsets within a file that are integer multiples of the volume sector size. 
          //File access must be for numbers of bytes that are integer multiples of the volume sector size. For example, if the sector size is 512 bytes, an application can request reads and writes of 512, 1024, or 2048 bytes, but not of 335, 981, or 7171 bytes. 
          //Buffer addresses for read and write operations should be sector aligned, which means aligned on addresses in memory that are integer multiples of the volume sector size. Depending on the disk, this requirement may not be enforced. 
          //One way to align buffers on integer multiples of the volume sector size is to use VirtualAlloc to allocate the buffers. It allocates memory that is aligned on addresses that are integer multiples of the operating system's memory page size. Because both memory page and volume sector sizes are powers of 2, this memory is also aligned on addresses that are integer multiples of a volume sector size.
        //
        //An application can determine a volume sector size by calling the GetDiskFreeSpace function."
        //CFile::osNoBuffer 
        ,&cfe)
        )
      {
        //Use "try" block because for instance data carrier may 
        //become unavailable or file is deleted since opening the 
        //file.
        try
        {
#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
          mp_o2oapp->m_ullProtocolFileLength = mp_o2oapp->
            m_fileFileAndDirChangeProtocol.GetLength();
          //BYTE * pbyBuffer=
          mp_o2oapp->m_pbyProtocolFileData = new BYTE[(unsigned int)
            mp_o2oapp->m_ullProtocolFileLength ];
          //Allocation succeeded.
          if(mp_o2oapp->m_pbyProtocolFileData)
          {
            UINT uiBytesRead = mp_o2oapp->m_fileFileAndDirChangeProtocol.Read(
              mp_o2oapp->m_pbyProtocolFileData,
              (UINT)mp_o2oapp->m_ullProtocolFileLength);
            if(uiBytesRead == mp_o2oapp->m_ullProtocolFileLength)
            {
              mp_o2oapp->m_bFileOpenedSuccessfully=true;
            }
            else
              delete mp_o2oapp->m_pbyProtocolFileData;
          }
#else //#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
          mp_protocolfiledata->m_ullProtocolFileLength = 
            mp_protocolfiledata->
            m_fileFileAndDirChangeProtocol.GetLength();
          //BYTE * pbyBuffer=
          mp_protocolfiledata->m_pbyProtocolFileData = new BYTE[(unsigned int)
            mp_protocolfiledata->m_ullProtocolFileLength ];
          //Allocation succeeded.
          if(mp_protocolfiledata->m_pbyProtocolFileData)
          {
            UINT uiBytesRead = mp_protocolfiledata->
              m_fileFileAndDirChangeProtocol.Read(
              mp_protocolfiledata->m_pbyProtocolFileData,
              (UINT)mp_protocolfiledata->m_ullProtocolFileLength);
            if(uiBytesRead == mp_protocolfiledata->m_ullProtocolFileLength)
            {
              mp_protocolfiledata->m_bFileOpenedSuccessfully=true;
            }
            else
              delete mp_protocolfiledata->m_pbyProtocolFileData;
          }
#endif //#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
        }
        catch(CFileException * pcfe)
        {
          //Use CFileException::Delete() and not delete CFileException * !
          pcfe->Delete();
          std::string strMessage = "Fehler beim Lesen der Protokoll-Datei" + 
            //rcstrFilePath ;
            rcstdstrFilePath ;
          mp_userinterface->ShowMessage( 
            //"Fehler beim Lesen der Protokoll-Datei" + 
            //std::string( (LPCSTR) rcstrFilePath ) 
            strMessage
            ) ;
        }
      }
      else
      {
        std::string strMessage = "Fehler beim Versuch, die Protokoll-Datei \"" 
          +
          //std::string( (LPCSTR) rcstrFilePath ) + std::string("\"exklusiv zu öffnen\n:") +
          //std::string( (LPCSTR) ::GetLastErrorMessageString( ::GetLastError() ) ) ;
          //rcstrFilePath + "\"exklusiv zu öffnen\n:" + 
          rcstdstrFilePath + "\"exklusiv zu öffnen\n:" + 
          std::string( 
          ::GetLastErrorMessageString( ::GetLastError() 
          )
          );
        mp_userinterface->ShowMessage(
          //std::string("Fehler beim Versuch, die Protokoll-Datei \"") +
          //std::string( (LPCSTR) rcstrFilePath ) + std::string("\"exklusiv zu öffnen\n:") +
          //std::string( (LPCSTR) ::GetLastErrorMessageString( ::GetLastError() ) )
          strMessage
          );
      }
#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
      return mp_o2oapp->m_bFileOpenedSuccessfully;
#else
      return mp_protocolfiledata->m_bFileOpenedSuccessfully;
#endif //#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
    }

void CreateDirectoriesIfTheyDontExist(
  const CString & strFullPathOfFileOrDirToSynchronize, 
  const CString &	strRootDirectoryToGetCopy,
  int nAmountOfCharactersOfRootPathToSynchronize
  )
{
	//voller Zielpfad ohne Dateiname
	CString strFullPathOfDestinationFileWithoutFilename;
	DWORD dwFileAttributes;
	//Annahme/Zusicherung: jeder Pfad hat mindestens 1 Backslash
	ASSERT(strFullPathOfFileOrDirToSynchronize.
		ReverseFind('\\'));
	strFullPathOfDestinationFileWithoutFilename=
		//zunächst: voller Quellpfad ohne Dateiname
		(LPCTSTR)(strFullPathOfFileOrDirToSynchronize.
		Left(strFullPathOfFileOrDirToSynchronize.
		ReverseFind('\\')));
	strFullPathOfDestinationFileWithoutFilename=
		//dann: Wurzelverzeichnis, dass die Kopien beinhalten
		//soll+...
		strRootDirectoryToGetCopy+
		//...voller Zielpfad ohne Dateiname und ohne 
		//Wurzelverzeichnis, dass synchronisiert/nach 
		//Änderungen überwacht werden soll
		strFullPathOfDestinationFileWithoutFilename.Right(
		strFullPathOfDestinationFileWithoutFilename.GetLength()-
		nAmountOfCharactersOfRootPathToSynchronize);

	//wenn der volle Zielverzeichnis-Pfad OHNE Dateiname noch
	//nicht existiert (z.B. wurde die Synchronisation erst
	//NACH der Erstellung dieses Ordners gestartet),...
	if((dwFileAttributes=GetFileAttributes((LPCTSTR)
		strFullPathOfDestinationFileWithoutFilename))==
		0xFFFFFFFF)
	{
		//...dann die fehlenden Ordner erstellen
		if(!CreateDirectory(strFullPathOfDestinationFileWithoutFilename,
			NULL))
			;
			//IDC_MESSAGE_LIST		
	}
}

bool FileExists(const CString & rcstrFullPathOfFileToProof)
{
	bool bFileExists=false;
	DWORD dwFileAttributes;
  if( ( dwFileAttributes = ::GetFileAttributes((LPCTSTR)
		  rcstrFullPathOfFileToProof)
      ) !=//0xFFFFFFFF
      INVALID_FILE_ATTRIBUTES
    )
	  //wenn die Funktion GetFileAttributes erfolgreich war
		//es kann sein, dass ein Verzeichnis auf der Seite der
		//zu erhaltenden Synchronisation/Kopien noch NICHT
		//existiert! (z.B. lief dieses Programm NICHT die ganze
		//Zeit mit, Zugriffsrechte verweigert etc.)

		//wenn der Quellpfad ein Verzeichnis ist
		if(!(dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			bFileExists=true;
	return bFileExists;
}

BOOL FileOrDirToSynchronizeExistsAndOrCanBeAdded(
  const CString & strFullPathOfLatestFileOrDirectoryToSynchronize,
  BYTE & rbyStateOfFileExistance
  )
{
	BOOL bFileOrDirExistsAndOrCanBeAdded = FALSE;
  if( ::GetFileAttributes((LPCTSTR)
		strFullPathOfLatestFileOrDirectoryToSynchronize) ==
		0xFFFFFFFF)
		//wenn die Funktion GetFileAttributes fehlschlug
	{
		DWORD dwLastError;
		dwLastError = GetLastError();
		rbyStateOfFileExistance=
			FILE_OR_FOLDER_TO_SYNCHRONIZE_DOES_NOT_EXIST;
		TRACE("GetFileAttributes schlug fehl - dwLastError: %u\n",
			dwLastError);

		if
		(AfxMessageBox
			((LPCTSTR)
				("Es gab einen Fehler beim "
					"Versuch, Attribute der/des zu synchronisierenden "
					"Datei/Verzeichnisses \n\""
					+strFullPathOfLatestFileOrDirectoryToSynchronize
					+"\"\n zu erhalten: "+GetLastErrorMessageString
					(
						dwLastError
					)+" Dies kann durch ein(e) nicht "+
					"existierende(s) Datei/Verzeichnis hervorgerufen "
					"worden sein.\nDen Pfad dennoch hinzufügen (zum "
					"Beispiel wird ein nicht existierender Pfad später"
					" hinzugefügt)?"
				),MB_YESNO|MB_ICONEXCLAMATION,NULL
			)==IDYES
		)
			bFileOrDirExistsAndOrCanBeAdded=TRUE;
	}
	else
	{
		rbyStateOfFileExistance=
			FILE_OR_FOLDER_TO_SYNCHRONIZE_EXISTS;
		bFileOrDirExistsAndOrCanBeAdded=TRUE;
	}
	return bFileOrDirExistsAndOrCanBeAdded;
}

//Rückgabe: eventueller Fehlercode, falls Verzeichnis 
//nicht erstellt werden konnte
//ERROR_SUCCESS bei erfolgreicher Verzeichnis-Esrtellung, oder
//wenn kein Verzeichnis erstellt wurde
DWORD 
#ifdef USE_NAMESPACES_INSTEAD_OF_MVC_PREFIXES
    MFC::
#endif // #ifdef USE_NAMESPACES_INSTEAD_OF_MVC_PREFIXES
    CreateMissingDirLevelsOfDirPath(
  const CString & strFullDirPath
  ,int & nIndexOfBackslashWhereErrorOccured,
  CLookForChangesWithinDirDlg * plookforchangeswithindirdlg
  )
{
	WORD wNumberOfDirsToCreate=0;
	//do
	//{
	//	if(
	//}
	CString strDirPath=strFullDirPath;
	int nIndexOfLastBackslash;
	nIndexOfLastBackslash=strDirPath.ReverseFind('\\');
  TRACE("CreateMissingDirLevelsOfDirPath(%s) Anfang\n",
    strFullDirPath);

	//wenn ein Backslash gefunden wurde und dieser 
	//das letzte Zeichen der Zeichenkette ist
	if(nIndexOfLastBackslash!=-1 && nIndexOfLastBackslash==
		strDirPath.GetLength()-1)
		strDirPath=strDirPath.Left(nIndexOfLastBackslash);
  CString strCurrentAction;
  strCurrentAction.Format("überprüfe, ob das Zielverzeichnis \"%s\" existiert",
    strDirPath);
  //TRACE("überprüfe, ob das Zielverzeichnis \"%s\" existiert\n"
  theApp.SetCurrentAction(strCurrentAction,
    plookforchangeswithindirdlg);
  TRACE("vor !DirExists(%s), ms:%u\n",strDirPath,GetTickCount());
  //wenn der Pfad ein UNC-Pfad mit Freigabenamen ist
  //"?*"<=>mindestens 1 Zeichen
  //if(wildcmp((LPCSTR)strDirPath,"\\\\?*\*")
  if(wildcmp((LPCSTR)strDirPath,"\\\\?*")
    )
  {
    //char * pch=(LPCSTR)strDirPath
    WORD wNumberOfBackslashes=0;
    for(WORD wIndex=0;wIndex<strDirPath.GetLength();++wIndex)
      if(strDirPath.GetAt(wIndex)=='\\')
        ++wNumberOfBackslashes;
    //ist eine Endlosschleife bei Konstruktionen wie "\OneToOneSynchronizer"
    while(wNumberOfBackslashes-wNumberOfDirsToCreate>
      //größer als 3, da die ersten 3 Backslashes den UNC-Pfad plus
      //Freigabename bilden (also z.B.:"\\10.8.0.1\stefan") und WEder
      //versucht werden soll, ein Verzeichnis, das den Pfad des 
      //Freigabenamens hat, zu erstellen (also z.B.:"stefan")noch 
      //versucht werden soll,
      //ein Verzeichnis, das den Pfad, des Rechner-Namens (also 
      //z.B.:"\\10.8.0.1")hat zu erstellen
      3 &&
      !DirExists(strDirPath))
    {
      TRACE("nach !DirExists(%s), ms:%u\n",strDirPath,GetTickCount());
	    nIndexOfLastBackslash=strDirPath.ReverseFind('\\');
	    //wenn ein Backslash gefunden wurde UND dieser nicht das
	    //letzte Zeichen des Pfades ist
	    if(nIndexOfLastBackslash!=-1 && nIndexOfLastBackslash!=
		    strDirPath.GetLength()-1)
		    //wenn 
		    if(nIndexOfLastBackslash>0)// && strDirPath.GeAt(
			    //nIndexOfLastBackslash)!=':')
		    {
			    strDirPath=strDirPath.Left(nIndexOfLastBackslash);
			    ++wNumberOfDirsToCreate;
		    }
      //wenn kein Backslash gefunden wurde 
	    if(nIndexOfLastBackslash==-1)
		    break;
      strCurrentAction.Format("überprüfe, ob das Zielverzeichnis \"%s\" existiert",
        strDirPath);
      theApp.SetCurrentAction(strCurrentAction,
        plookforchangeswithindirdlg);
    }
  }
  else
  {
	  //ist eine Endlosschleife bei Konstruktionen wie "\OneToOneSynchronizer"
	  while(!DirExists(strDirPath))
	  {
      TRACE("nach !DirExists(%s), ms:%u\n",strDirPath,GetTickCount());
		  nIndexOfLastBackslash=strDirPath.ReverseFind('\\');
		  //wenn ein Backslash gefunden wurde UND dieser nicht das
		  //letzte Zeichen des Pfades ist
		  if(nIndexOfLastBackslash!=-1 && nIndexOfLastBackslash!=
			  strDirPath.GetLength()-1)
			  //wenn 
			  if(nIndexOfLastBackslash>0)// && strDirPath.GeAt(
				  //nIndexOfLastBackslash)!=':')
			  {
				  strDirPath=strDirPath.Left(nIndexOfLastBackslash);
				  ++wNumberOfDirsToCreate;
			  }
      //wenn kein Backslash gefunden wurde 
		  if(nIndexOfLastBackslash==-1)
			  break;
      strCurrentAction.Format("überprüfe, ob das Zielverzeichnis \"%s\" existiert",
        strDirPath);
      theApp.SetCurrentAction(strCurrentAction,plookforchangeswithindirdlg);
	  }
  }
  //damit der Text zur gegenwärtigen Aktion nicht bis zur nächsten
  //Änderung stehen bleibt
  theApp.SetCurrentAction("",plookforchangeswithindirdlg);
	//int nIndexOfLastBackslash;
	for(WORD wRun=0;wRun<wNumberOfDirsToCreate-1;++wRun)
	{
		nIndexOfLastBackslash=strFullDirPath.Find('\\',
			strDirPath.GetLength()+1);
		//wenn ein Backslash hinter (rechts von) "Länge von 
		//strDirPath" gefunden wurde
		if(nIndexOfLastBackslash!=-1)
		{
			strDirPath=strFullDirPath.Left(nIndexOfLastBackslash);
			//CreateDirectory kann nur für 1 Verzeichnisebene
			//genommen werden, und nicht für einen ganzen Pfad
			if(!CreateDirectory(strDirPath,NULL))
			{
				nIndexOfBackslashWhereErrorOccured=
					nIndexOfLastBackslash;
				return ::GetLastError();
			}
		}
	}
	//weil nach dem vollen Verzeichnisnamen kein Backslash mehr
	//folgt, zuletzt das Verzeichnis mit der höchsten Verzeichnis-
	//tiefe erstellen
	if(wNumberOfDirsToCreate>0)
		if(!CreateDirectory(strFullDirPath,NULL))
		{
			nIndexOfBackslashWhereErrorOccured=
				nIndexOfLastBackslash;
			return ::GetLastError();
		}
	return ERROR_SUCCESS;
}
