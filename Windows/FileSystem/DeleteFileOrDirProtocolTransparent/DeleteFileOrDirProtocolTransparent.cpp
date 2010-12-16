
typedef unsigned char BYTE ;
//  #ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
//Protocol transparent means: no protocol such as FTP must be handled,
//everything works as if it happens lokally via the normal Windows API
//(::CopyFile()). This (also) concerns the SMB(Windows shares) protocol.
BYTE DeleteFileOrDirProtocolTransparent(
  const CString & rcstrFullPathOfFileOrDirOnSideToBeSynchronized,
  BYTE byObjectIsAFile //,
  //CLookForChangesWithinDirDlg * plookforchangeswithindirdlg
  )
{
  BYTE byReturn=DESTINATION_UNREACHABLE;
  //bool bCopiedSuccessfullyReturn;

  //TRACE("On_FileRemoved(-%s\n",strRelativePathOfFileOrDirToSynchronize);
  //TRACE("Thread-ID dieses Threads:%u\n",GetCurrentThreadId());

  {
    //CString strFullDestinationFileOrDirPath;
    //if(//das Ziellaufwerk kann eventuell gerade nicht
    //	//verf?gbar sein->auch in diesem Fall protokollieren
    //	!DirOrAnySuperDirExists(
    //	rcstrFullPathOfFileOrDirOnSideToBeSynchronized))
    //{
    //	//bLogChanges=true;
    //	//vecIndexOfDestinationToLog.push_back(wRun);
    //	//byReturn=DESTINATION_UNREACHABLE;
    //}
    //else
    //	//++wNumberOfWriteChangesImmediately;
    //{
      //DWORD dwFileAttributes;
      //ASSERT(pDirWatchInfo->
      //	m_ptypedptrarraydestdiratts->ElementAt(wRun)->
      //	m_strDestinationDirToReceiveChanges.
      //	Right(1)=="\\");
      //strFullDestinationFileOrDirPath=pDirWatchInfo->
      //	m_ptypedptrarraydestdiratts->ElementAt()->
      //	m_strDestinationDirToReceiveChanges+
      //	strRelativePathOfFileOrDirToSynchronize;
      //strFullDestinationFileOrDirPath=
      //	::GetFullPathOfFileOrDirOnSideToBeSynchronized(
      //	pDirWatchInfo->m_ptypedptrarraydestdiratts->
      //	ElementAt(
      //	wRun),
      //	rcstrRelativePathOfFileOrDirToSynchronize);

      ////NICHT den Pfad der QUELL-Datei/-Verzeichnis
      ////als Parameter an GetFileAttributes
      ////?bergeben, denn sonst tritt der Windows-Fehler
      ////"Das System kann die angegebene Datei nicht finden",
      ////denn man kann ja keine Attribute ?ber eine Datei/ein
      ////Verzeichnis erhalten, da die Datei/das Verzeichnis bereits
      /////vorhin gel?scht wurde!
      ////Wenn KEINE Attribute der Datei/des Verzeichnis auf der
      ////Seite, die die Spiegelung bei der Synchronisation sein soll
      ////erhalten werden konnten
      //if((dwFileAttributes=GetFileAttributes((LPCTSTR)
      //	rcstrFullPathOfFileOrDirOnSideToBeSynchronized))==0xFFFFFFFF)
      ////wenn die Funktion GetFileAttributes fehlschlug
      //{
      //	//Manche Programme scheinen zeitlich VOR dem eigentlichen
      //	//Speichern eine(n) Datei(-pfad/-namen) schon mal anuzulegen
      //	//und danach wieder zu l?schen. Das ist also nicht immer
      //	//ein wirklicher/ernsthafter Fehler
      //	WriteToMessagesWindow("Attribute der/des "
      //		"gel?schten Datei/Verzeichnis \""+
      //		rcstrFullPathOfFileOrDirOnSideToBeSynchronized+
      //		"\" nicht erhalten:"+
      //		GetLastErrorMessageString(GetLastError()));
      //	byReturn=GET_FILE_ATTRIBUTES_FAILED;
      //}
      ////wenn die Funktion GetFileAttributes erfolgreich war
      //else
      //{
        //wenn der Quellpfad ein Verzeichnis ist
        if(//dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY
          ! byObjectIsAFile )
        {
          if( ::RemoveDirectory( (LPCTSTR)
            rcstrFullPathOfFileOrDirOnSideToBeSynchronized) )// pointer to directory to remove
          {
            theApp.
            WriteToMessagesWindow("Verzeichnis \""+
              rcstrFullPathOfFileOrDirOnSideToBeSynchronized+
              "\" erfolgreich gel?scht");
            byReturn = SUCCESS;
          }
          //wenn RemoveDirectory fehlschlug
          else
          {
            theApp.
            WriteToMessagesWindow("L?schen des"
              "Verzeichnis' \""+
              rcstrFullPathOfFileOrDirOnSideToBeSynchronized+
              "\" schlug fehl:"+GetLastErrorMessageString(
              GetLastError() )
              );
            byReturn=FAILURE;
          }
        }
        else
          //vorher noch einen eventuellen Schreibschutz entfernen?
          if( ::DeleteFile(rcstrFullPathOfFileOrDirOnSideToBeSynchronized) )
          {
            byReturn = SUCCESS;
            theApp.
            WriteToMessagesWindow("Datei \""+
              rcstrFullPathOfFileOrDirOnSideToBeSynchronized+
              "\" gel?scht");
          }
          //wenn DeleteFile fehlschlug
          else
          {
            theApp.
            WriteToMessagesWindow("L?schen der "
              "Datei \""+
              rcstrFullPathOfFileOrDirOnSideToBeSynchronized+
              "\" schlug fehl:"+GetLastErrorMessageString(
              GetLastError()));
            byReturn=FAILURE;
          }
      //}//wenn die Funktion GetFileAttributes erfolgreich war
    //}
  }
  return byReturn;
}
