/*
 * GnuPG.cpp
 *
 *  Created on: Nov 11, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else g++ compilation errors like
//" error: `GetFileAttributesA' cannot be used as a function" .
#include <windows.h> //::CreateProcess(...), GetFileAttributes(...) [,...]
#include "GnuPG.hpp" //STARTING_ECRYPTION_PROCESS_SUCCEEDED etc.
#ifndef _MSC_VER
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif
#include <preprocessor_macros/trace.h> //TRACE(...)
#include <Windows/AppendCurrentTimeToString/AppendCurrentTimeToString.hpp>
//#include <constants.h> //STARTING_ECRYPTION_PROCESS_SUCCEEDED
#include <tchar.h> //_T(...)

typedef unsigned char BYTE ;

BYTE PossiblyEncryptFile(
  const CString & strFullPathOfFileOrDirToSynchronize,
  const CString & strFullPathOfFileOrDirOnSideToBeSynchronized,
  //std::vector<CString> * pvecstrExtensionsToEncrypt,
  const CString & rcstrUserForGnuPG,
//  DestinationDirAttributes * pDestinationDirAttributes,
  HANDLE & rhProcess,
  CString & rstrFullTempDestinationFilePath,
  CString & strPathToEncryptionProgram ,
//  CLookForChangesWithinDirDlg * plookforchangeswithindirdlg,
  BYTE byCreateFileNameWithAppendedTimeFirst//=ALWAYS
  )
{
  bool bNotCopiedYet = true;
  BYTE byReturn = GnuPG::STARTING_ECRYPTION_PROCESS_SUCCEEDED;
  TRACE("COneToOneSynchronizerApp::EventuallyEncryptFile Anfang\n");
  //if(pvecstrExtensionsToEncrypt)
  //{
    //if(//IsInListOfExtensionsForFilesToEncrypt(
    ////pDirWatchInfo->m_pvecstrExtensionsToEncrypt,
    ////)
    //  FileExtensionIsIncludedInVector(
    //    strFullPathOfFileOrDirToSynchronize,
    //    pvecstrExtensionsToEncrypt)
    //  )
    //{
      /*CString strCommandline=
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        //"\""+
        //m_strPathToEncryptionProgram+
        ////sicherheitshalber doppelte Anführungszeichen,
        ////es können ja Leerzeichen im Pfad sein
        //"\""+
        " -e --yes -r "
        "\"Stefan Gebauer\" -o "
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\""+
        strFullPathOfFileOrDirOnSideToBeSynchronized+
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\" \""+
        strFullPathOfFileOrDirToSynchronize+
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\"";*/
      //Beispiel:
      //C:\Programme\GNUPG\gpg -e --yes -r \
      //"Stefan Gebauer" -o "D:\Backup\geheim.txt" \
      //"C:\DuE\Stefan\geheim.txt"
      CString strCommandLine;
      DWORD dwErrorCodeForCreateMissingDirLevelsOfDirPath;
      int nIndexOfBackslashWhereErrorOccured;
      STARTUPINFO startupinfo;
      ZeroMemory( & startupinfo,sizeof(startupinfo));
      PROCESS_INFORMATION process_Information;
      ZeroMemory( & process_Information,sizeof(process_Information) );
      startupinfo.cb = sizeof(startupinfo);
      startupinfo.dwFlags = STARTF_USESTDHANDLES |
        //STARTF_USESHOWWINDOW spezifizieren, damit
        //sInfo.wShowWindow ausgewertet wird
        STARTF_USESHOWWINDOW;
      startupinfo.hStdInput = NULL;
      //Damit sich das KonsolenFenster von gnupg nicht in
      //den Vordergrund drängt.
      startupinfo.wShowWindow = SW_SHOWMINNOACTIVE;

      {
        bool bCreateFileNameWithAppendedTimeFirst = false;
        //CString strFullTempDestinationFilePath;
        rstrFullTempDestinationFilePath =
          strFullPathOfFileOrDirOnSideToBeSynchronized;
        if(//pDestinationDirAttributes->
          //m_byCreateFileNameWithAppendedTimeFirst
          byCreateFileNameWithAppendedTimeFirst == GnuPG::ONLY_IF_NOT_EXISTANT)
        {
          DWORD dwFileAttributes;
          //Wenn Attribute der Datei/des Verzeichnis auf der
          //Seite, die die Spiegelung bei der Synchronisation sein soll
          //erhalten werden konnten.
          if( ( dwFileAttributes = ::GetFileAttributes( (LPCTSTR)
              strFullPathOfFileOrDirOnSideToBeSynchronized) ) != 0xFFFFFFFF
            )
          {
            bCreateFileNameWithAppendedTimeFirst = true;
          }
        }
        if(//pDestinationDirAttributes->
          //m_byCreateFileNameWithAppendedTimeFirst
          byCreateFileNameWithAppendedTimeFirst == GnuPG::ALWAYS )
          bCreateFileNameWithAppendedTimeFirst = true;
        //To copy indirect(that means to copy to an INTERMEDIATE filename
        //and rename afterwards) is the SAFER method. Imagine that one
        //copies to a filename that belongs to a file with a previously
        //modified version that has important changes. And then the content
        //of this file is overwritten with the new content. And when then
        //the write process doesn't finish, the destination file may be
        //unusable and the BACKUP purpose ist not satisfied.
        //Probably it's also better to take a temporary filename if the final
        //file name (without time) not already exists?(because it may be
        //created while copying)
        if(bCreateFileNameWithAppendedTimeFirst)
        {
          //So we better copy to a destination file with intermediate
          //filename. Let's append the time of when the copying starts to
          //the filename. SO one knows what the file stands for if the
          //transaction of indirect copy is not finished, that means, if
          //for example THIS program crashes or the connection disconnects.

          //Append the current time to the string BEFORE we check the
          //file path length because it gets longer.
          //Synchronize::
          AppendCurrentTimeToString( rstrFullTempDestinationFilePath);
        }
      strCommandLine = CString(
        //"-e" = encrypt
                //"yes" bedeutet: automatisch/implizit "ja" antworten:
                //z.B. auf die Frage: "Datei '...gpg' existiert bereits.
                //überschreiben?(j/N)"-> sinnvoll, da von einer Datei
                //mehrmals gpg-Dateien erzeugt werden können.
                //"-r" = encrypt for user id name.
        _T(" -e --yes -r "
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\"") +
//        pDestinationDirAttributes->m_strUserForGnuPG+
        rcstrUserForGnuPG +
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\"" +
        //"-o" bedeutet: den Ziel-Dateinamen selbst
        //festlegen
        " -o "
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\"" +
        rstrFullTempDestinationFilePath +
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\" \"" +
        strFullPathOfFileOrDirToSynchronize +
        //sicherheitshalber doppelte Anführungszeichen,
        //es können ja Leerzeichen im Pfad sein
        "\""
        );
        //nur wenn der VOLLE Zielpfad existiert(Voraussetzung für GnuPG)
        //, braucht versucht zu werden, die Datei zu verschlüsseln
        //(sonst braucht der Prozess noch Mal einiges an zeit, bis
        //gemerkt wird, dass der Zielpfad gar nicht erreichbar ist
        if( ::CreateProcess(
            //CString("\""+
            strPathToEncryptionProgram
            //+"\"")
            ,
            (WCHAR *) strCommandLine.GetBuffer( //strCommandLine.GetLength()
              ),
            NULL,
            NULL,
            TRUE,
            NORMAL_PRIORITY_CLASS,//|CREATE_NO_WINDOW,
            NULL,
            NULL,
            & startupinfo,
            & process_Information
            )
          )
        {
          //If the function succeeds, the return value is nonzero
          bNotCopiedYet = false;
          //zu jedem Laufwerk/ UNC-Pfad soll zur gleichen
          //Zeit nur 1 Schreibvorgang für diesen PROZESS möglich
          //sein
          //UniqueDestinationUNC_PathesAndDrives.
          //  m_EncryptionTask.add(process_Information.hProcess);
          //Add
          rhProcess = process_Information.hProcess;
        }
        else
        {
          byReturn = GnuPG::ERROR_STARTING_ECRYPTION_PROCESS;
        }
        TRACE("gnupg:%s\n", strFullPathOfFileOrDirOnSideToBeSynchronized);
      }
      //nach dem Aufruf von GnuPG müsste noch der Exit-Code abgefragt
      //werden?!(0=Erfolg)

      //ExecuteExternalFile(
      //  CString("\""+m_strPathToEncryptionProgram+"\""),
      //  strCommandLine);
      //shellexecute(0,'open','c:\cmd.exe','','c:\',SW_NORMAL);

    //}
    //else
    //  byReturn=EXTENSION_IS_NOT_IN_LIST_OF_FILES_TO_ENCRYPT_OR_LIST_IS_EMPTY;
  //}
  //else
  //  byReturn=EXTENSION_IS_NOT_IN_LIST_OF_FILES_TO_ENCRYPT_OR_LIST_IS_EMPTY;
  TRACE("EventuallyEncryptFile Ende\n");
  return byReturn;
}
