/*
 * FileSystem.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: Stefan
 */
//Make "windows.h" as the 1st include: else g++ compilation errors like
//" error: `GetFileAttributesA' cannot be used as a function" .
#include <windows.h> //::GetFileAttributes(...)
#ifndef _MSC_VER //if not MS compiler
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif //#ifndef _MSC_VER
#include <preprocessor_macros/trace.h> //TRACE(...)
//GetLastErrorMessageString(...)
#include <Windows/ErrorCode/ErrorCodeFromGetLastErrorToString.h>

#include <windef.h> //WORD
#include <vector> //class std::vector
#include <string> //std::basic_string::size_type
#include <tchar.h> //_T(...)

  DWORD CheckDestinationDirectory(
    const CString & crstrFullPathOfLatestDestinationDirectory,
    DWORD & rdwLastError,
    int & rnStartWatch,
    const CString * pstrAppend,
    const CString * pstrInsert,
    bool & bPathIsADirectory
    )
  {
    DWORD dwFileAttributes;
    //Erst initialisieren mit dem Wert eines Erfolgs für
    //den Fall, dass GetFileAttributes NICHT fehlschlägt
    rdwLastError = ERROR_SUCCESS;
    TRACE("crstrFullPathOfLatestDestinationDirectory: %s\n",
      crstrFullPathOfLatestDestinationDirectory);
    if( ( dwFileAttributes = ::GetFileAttributes( (LPCTSTR)
        crstrFullPathOfLatestDestinationDirectory) ) == 0xFFFFFFFF
      )
    //wenn die Funktion GetFileAttributes fehlschlug
    {
      TRACE("die Funktion GetFileAttributes schlug fehl\n");
      //Zuerst GetLastError aufrufen, damit der Fehlercode
      //nicht durch eine nachfolgende Funktion überschrieben wird
      rdwLastError = ::GetLastError();
      //wenn der Zeiger "NULL" ist
      if( ! pstrAppend )
      {
        pstrAppend = new CString();
      }
      std::tstring stdtstrMessage = std::tstring(
        _T("Es gab einen Fehler beim Versuch, Attribute des "
        "Zielverzeichnis-Pfades \n\"")
        )
        + crstrFullPathOfLatestDestinationDirectory
        + _T("\"\nzu erhalten: ") +
        GetStdTstring_Inline(
          GetLastErrorMessageString
          (
            rdwLastError
          )
        )
        + std::tstring( _T("Dies kann durch ein(e) nicht "
        "existierende(s) Datei/Verzeichnis hervorgerufen worden sein.\n"
        "Achtung: falls das Verzeichnis noch nicht existiert, fügen Sie es "
        "am besten noch VOR dem Betätigen der Schaltfläche \"Ja\" "
        "hinzu! Denn falls Sie die Schaltfläche \"Ja\" betätigen, wird das "
        "Überwachen/ Beobachten zwecks des Synchronisierens direkt danach "
        "gestartet. "
        "Falls dann eine Veränderung in dem zu synchronisierenden "
        "Verzeichnis auftritt, KANN es zu einem Fehler kommen.")
        )
        +
        * pstrAppend ;
      rnStartWatch = //::AfxMessageBox
        ::MessageBox
        (
          NULL,
//          (LPCTSTR)
//          (
//            stdtstrMessage
//            //"\nDas Überwachen/ Beobachten zwecks des "
//            //"Synchronisierens des Pfades "+
//            //"dennoch starten?"
//          )
          stdtstrMessage.c_str()
          , NULL
          ,MB_YESNO | MB_ICONEXCLAMATION
          //, NULL
        );
      if(rnStartWatch == IDYES)
        ;
      //if(pstrAppend)
      //delete pstrAppend;
    }
    else
    //wenn die Funktion GetFileAttributes
    //erfolgreich war
    {
      //wenn der Pfad kein Verzeichnis ist
      if( ! (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
      {
        bPathIsADirectory = false;
        rnStartWatch = IDNO;
        ////wenn das �berwachen/Beobachten zwecks "
        ////des Synchronisierens direkt danach starten w�rde
        //if(m_byDifferenceInItemsBetweenListBoxes==
        //  LIST_WITH_OBJECTS_TO_SYNCHRONIZE_HAS_ONE_ITEM_MORE_THAN_LIST_WITH_DESTINATION_DIRECTORIES)
        //{
          //wenn der Zeiger "NULL" ist
          if( ! pstrInsert)
          {
            pstrInsert = new CString();
          }
          std::tstring stdtstrMessage =
            std::tstring( _T("Der angegebene Pfad ist KEIN Verzeichnis.\n"
            "Der Zielpfad MUSS aber ein Verzeichnis sein.\n")
            )
            + * pstrInsert +
            std::tstring( _T("Das Überwachen/ Beobachten zwecks des "
              "Synchronisierens wird NICHT gestartet.")
            ) ;
//          ::AfxMessageBox
          ::MessageBox
          (
            NULL ,
//            (LPCTSTR)
//            (
//            )
            stdtstrMessage.c_str()
            , NULL
            ,MB_OK | MB_ICONSTOP
//            , NULL
          );
          //delete pstrInsert;
        //}
        /*//wenn das Überwachen/ Beobachten zwecks "
        //des Synchronisierens NOCH NICHT direkt danach
        //starten würde
        else
        {
          AfxMessageBox
          ((LPCTSTR)
            ("Der angegebene Pfad ist KEIN Verzeichnis.\n"
              "Der Zielpfad MUSS aber ein Verzeichnis sein.\n"
              +strInsert+
            ),MB_OK|MB_ICONSTOP,NULL
          );
        }*/
      }
      else
        bPathIsADirectory = true;
    }//Ende von: wenn die Funktion GetFileAttributes NICHT
    //erfolgreich war*/
    return dwFileAttributes;
  }

//fuer die spaetere Verkettung(wenn man den VOLLEN Zielpfad
//erstellt), macht es sich am besten(und am schnellsten), wenn der Wurzel-
//Zielpfad bereits genau 1 Backslash am Ende hat.
CString GetDirWith1TrailingBackslash(CString strDestinationDir)
{
  if( strDestinationDir.Right(1) == "\\" )
  {
    int nIndexOfBackslash = strDestinationDir.GetLength();
    //Wert ungleich 0 ist true und bei while kann ohne
    //diese Prüfung bei leerer Zeichenkette eine -1 rauskommen
    if( nIndexOfBackslash > 1 )
    {
      //int nIndexOfLeadingBackslashOfLastConsecutiveBackslashes;
      -- nIndexOfBackslash;
      while( -- nIndexOfBackslash )
        //if(strDestinationDir[nIndexOfBackslash]=='\\')
          //nIndexOfLeadingBackslashOfLastConsecutiveBackslashes=
          //  nIndexOfBackslash;
        //else
        if( //strDestinationDir[nIndexOfBackslash]
            strDestinationDir.GetAt( nIndexOfBackslash ) != '\\' )
        {
          //wenn mehr als 1 Backslash am Ende der Zeichenkette
          if( nIndexOfBackslash != strDestinationDir.GetLength() - 2 )
            strDestinationDir = strDestinationDir.Left(
              nIndexOfBackslash + 1 );
          break;
        }
    }
  }
  else
    strDestinationDir += _T("\\") ;
  return strDestinationDir;
}

//diese Funktion ist wahrscheinlich noch NICHT perfekt:
//wenn der Zugriff verweigert wird, liefert
//GetFileAttributes sicherlich auch "0xFFFFFFFF" zurück
bool FileOnSideToBeSynchronizedExists(
  const CString & crstrFullPathOfFileOrDir)
{
  DWORD dwFileAttributes;
  if( ( dwFileAttributes = //::GetFileAttributes( (LPCTSTR)
      ::GetFileAttributesA( crstrFullPathOfFileOrDir) ) == 0xFFFFFFFF
    )
    return false;
  else
    return true;
}

bool FileExtensionIsIncluded(
  const CString & rcstrFullSourceFilePath,
  const std::vector<CString> & vecstrExtensions
  )
{
  bool bFileExtensionIsIncluded;
  CString strExtension;
  int nIndexOfLastDot;
  int nIndexOfLastBackslash;
  WORD vecstrExtensionsSize;

  vecstrExtensionsSize = vecstrExtensions.size();
  nIndexOfLastDot = rcstrFullSourceFilePath.ReverseFind('.');
  nIndexOfLastBackslash = rcstrFullSourceFilePath.
    ReverseFind('\\');
  bFileExtensionIsIncluded = true;

  //der Punkt, der Dateiname und -Endung trennt, muss HINTER
  //dem letzten Backslash liegen(das KANN der Fall sein bei
  //keiner Dateiendung)
  //nIndexOfLastDot ist -1, wenn kein Punkt im Pfadnamen
  //nIndexOfLastBackslash ist -1, wenn kein Punkt im
  //  Pfadnamen (duerfte aber unter normalen Umstaenden nicht
  //  moeglich sein, da hinter dem Laufwerksbuchstaben gleich
  //   ein ":\" steht
  if(nIndexOfLastDot > nIndexOfLastBackslash)
  {
    strExtension = rcstrFullSourceFilePath.Right(
      rcstrFullSourceFilePath.GetLength() - nIndexOfLastDot - 1 );
  }
  else
  {
    strExtension =
      //Avoid g++ warning "deprecated conversion from string constant to
      //'TCHAR*'"
      (TCHAR *) _T("") ;
  }
  //for(int nRun=0;nRun<vecstrExtensionsSize;++nRun)
  //Iterator ist vermutlich schneller, da nicht bei jedem
  //Scheliefendurchllauf das nächste Element wieder von
  //vorne beim Vektor durchlaufen werden muss.
  for(std::vector<CString>::const_iterator ci =
    vecstrExtensions.begin(); ci != vecstrExtensions.end(); ++ ci )
    //Zeichenketten sind identisch
    if( * ci == strExtension )
    {
      bFileExtensionIsIncluded=false;
      break;
    }
  return bFileExtensionIsIncluded;
}

bool FileExtensionIsIncludedInVector(
  const CString & rcstrFilePath,
  const std::vector<CString> * pvecstrExtensions)
{
  bool bFileExtensionIsIncluded=false;
  //wenn ungleich NULL
  if(pvecstrExtensions)
  {
    CString strExtension;
    int nIndexOfLastDot;
    int nIndexOfLastBackslash;
    WORD vecstrExtensionsSize;
    vecstrExtensionsSize=pvecstrExtensions->size();
    nIndexOfLastDot=rcstrFilePath.ReverseFind('.');
    nIndexOfLastBackslash=rcstrFilePath.
      ReverseFind('\\');
    //bFileExtensionIsIncluded=true;

    //der Punkt, der Dateiname und -Endung trennt, muss HINTER
    //(also auf der Seite der tieferen Verzeichnisebene)
    //dem letzten Backslash liegen(das ist nicht der Fall bei
    //keiner Dateiendung)
    //nIndexOfLastDot ist -1, wenn kein Punkt im Pfadnamen
    //nIndexOfLastBackslash ist -1, wenn kein Backslash im
    //  Pfadnamen (d�rfte aber unter normalen Umst�nden nicht
    //  m�glich sein, da hinter dem Laufwerksbuchstaben gleich
    //   ein ":\" steht
    if(nIndexOfLastDot>nIndexOfLastBackslash)
      //Dateiendung vorhanden
    {
      strExtension=rcstrFilePath.Right(
        rcstrFilePath.GetLength()-nIndexOfLastDot-1);
    }
    else
    {
      strExtension =
        //Avoid g++ warning "deprecated conversion from string constant to
        //'TCHAR*'"
        (TCHAR *) _T("") ;
    }
    //for(int nRun=0;nRun<vecstrExtensionsSize;++nRun)
    //Iterator ist vermutlich schneller, da nicht bei jedem
    //Schleifendurchlauf das n�chste Element wieder von
    //vorne beim Vektor durchlaufen werden muss
    for(std::vector<CString>::const_iterator ci =
      pvecstrExtensions->begin();ci != pvecstrExtensions->end(); ++ci)
      //Zeichenketten sind identisch
      if(*ci==strExtension)
      {
        //Dateiendung stimmt mit einer Dateiendung der
        //Ausschlussliste �berein->Dateiendung ist nicht
        //eingeschlossen
        bFileExtensionIsIncluded=true;
        break;
      }
  }
  return bFileExtensionIsIncluded;
}

bool ExtensionIsNotAlreadyIncluded(
  const std::vector<CString> & rcvecstrExtensions,
  const CString & crstrExtension)
{
  bool bExtensionIsNotAlreadyIncluded = true;
  //std::vectoriterator
  //for(int wRun=0;wRun<rcvecstrExtensions.size();++wRun)
  for( std::vector<CString>::const_iterator i = rcvecstrExtensions.begin() ;
      i != rcvecstrExtensions.end() ; ++ i )
  {
    //if(vecstrExtensions.at(wRun)==crstrExtension)
    if( * i == crstrExtension )
    {
      bExtensionIsNotAlreadyIncluded = false;
      break;
    }
  }
  return bExtensionIsNotAlreadyIncluded;
}

void ParseExcludeExtensionsFromCopying(
  const CString & str,
  std::vector<CString> & vecStrExcludeFileExtensionsFromCopying
  )
{
  bool bFirstColon = true;
  int wRun = 0 ;
  //auf MAXWORD setzen, damit das mit dem String extrahieren
  //bei beiden Bendigungen klappt und Quellcode nicht komplexer
  //(mehr Verzweigungen) wird: wenn plus 1, dann ist der Wert "0"
  WORD wIndexOfPreviousColon = MAXWORD;
  TRACE("MAXWORD: %u\n", MAXWORD);
  for( ; wRun < str.GetLength(); ++ wRun )
  {
    if( //str[wRun]
        str.GetAt(wRun) == ',' )
    {
      WORD wIndexOfFirstCharOfCurrentExtension =
        (WORD)( wIndexOfPreviousColon + 1 );
      //Zwischen diesem und dem vorgerigen Komma/ dem Anfang der Zeichenkette
      //muss nicht unbedingt 1 Zeichen außer eines Kommas liegen:eine leere
      //Erweiterung bedeutet kein Dateiende und daher auch kein Punkt bis
      //zum nächsten Backslash.
      if( ExtensionIsNotAlreadyIncluded(
        vecStrExcludeFileExtensionsFromCopying,
        str.Mid(wIndexOfFirstCharOfCurrentExtension, wRun -
        wIndexOfFirstCharOfCurrentExtension))
        )
        vecStrExcludeFileExtensionsFromCopying.push_back(
          str.Mid( wIndexOfFirstCharOfCurrentExtension,
          wRun - wIndexOfFirstCharOfCurrentExtension )
          );
      if(bFirstColon)
        bFirstColon = false;
      wIndexOfPreviousColon = wRun;
    }
  }
  //es gibt nur 1 Erweiterung
  //wenn die Zeichenkette leer ist, soll keine Erweiterung
  //ausgeschlossen werden
  if(bFirstColon && wRun>0)
    vecStrExcludeFileExtensionsFromCopying.push_back(str);
  //wenn es bereits mindestens 1 Komma gibt, dann ist die
  //letzte Erweiterung "" (keine/leere Erweiterung)
  if( ! bFirstColon )
  {
    CString strLastExtension;
    WORD wIndexOfFirstCharOfCurrentExtension=
      (WORD)(wIndexOfPreviousColon + 1 );
    strLastExtension = str.Mid(wIndexOfFirstCharOfCurrentExtension,
      wRun-wIndexOfFirstCharOfCurrentExtension);
    //zwischen diesem und dem vorgerigen Komma/dem Anfang
    //der Zeichenkette muss nicht unbedingt 1 Zeichen
    //au�er eines Kommas liegen:eine leere Erweiterung bedeutet
    //kein Dateiende und daher auch kein Punkt bis zum n�chsten
    //Backslash
    if(ExtensionIsNotAlreadyIncluded(
      vecStrExcludeFileExtensionsFromCopying,
      strLastExtension)
      )
    vecStrExcludeFileExtensionsFromCopying.push_back(
      strLastExtension);
  }
#ifdef _DEBUG
  for(int i=0;i<(int)vecStrExcludeFileExtensionsFromCopying.size();i++)
    TRACE("vecStrExcludeFileExtensionsFromCopying.at(i): %s\n",
    vecStrExcludeFileExtensionsFromCopying.at(i));
#endif
  //return vecStrExcludeFileExtensionsFromCopying;
}

std::vector<CString> ParseExcludeExtensionsFromCopying(
  const CString & str)
{
  //als Vektor deklarieren, da vorher nicht bekannt ist,
  //wieviele Elemente herauskommen
  std::vector<CString> vecStrExcludeFileExtensionsFromCopying;
  //auf MAXWORD setzen, damit das mit dem String extrahieren
  //bei beiden Bendigungen klappt und Quellcode nicht komplexer
  //(mehr Verzweigungen) wird: wenn plus 1, dann ist der Wert "0"
  WORD wIndexOfPreviousColon = MAXWORD;
  bool bFirstColon = true;
  int wRun = 0;

  TRACE("MAXWORD: %u\n", MAXWORD);
  for(; wRun < str.GetLength(); ++ wRun )
  {
    if( //str[wRun]
        str.GetAt(wRun) == ',' )
    {
      WORD wIndexOfFirstCharOfCurrentExtension =
        (WORD)(wIndexOfPreviousColon + 1 );
      //Zwischen diesem und dem vorgerigen Komma/ dem Anfang der Zeichenkette
      //muss nicht unbedingt 1 Zeichen außer eines Kommas liegen:eine leere
      //Erweiterung bedeutet kein Dateiende und daher auch kein Punkt bis zum
      //nächsten Backslash.
      if( ExtensionIsNotAlreadyIncluded(
          vecStrExcludeFileExtensionsFromCopying,
          str.Mid( wIndexOfFirstCharOfCurrentExtension ,
          wRun - wIndexOfFirstCharOfCurrentExtension )
          )
        )
        vecStrExcludeFileExtensionsFromCopying.push_back(
          str.Mid( wIndexOfFirstCharOfCurrentExtension , wRun -
          wIndexOfFirstCharOfCurrentExtension)
          );
      if(bFirstColon)
        bFirstColon = false ;
      wIndexOfPreviousColon = wRun;
    }
  }
  //es gibt nur 1 Erweiterung
  //wenn die Zeichenkette leer ist, soll keine Erweiterung
  //ausgeschlossen werden
  if( bFirstColon && wRun > 0 )
    vecStrExcludeFileExtensionsFromCopying.push_back(str);
  //wenn es bereits mindestens 1 Komma gibt, dann ist die
  //letzte Erweiterung "" (keine/leere Erweiterung)
  if( ! bFirstColon )
  {
    CString strLastExtension;
    WORD wIndexOfFirstCharOfCurrentExtension=
      (WORD)(wIndexOfPreviousColon+1);
    strLastExtension=str.Mid(wIndexOfFirstCharOfCurrentExtension,
      wRun-wIndexOfFirstCharOfCurrentExtension);
    //Zwischen diesem und dem vorgerigen Komma/ dem Anfang der Zeichenkette
    //muss nicht unbedingt 1 Zeichen außer eines Kommas liegen:eine leere
    //Erweiterung bedeutet kein Dateiende und daher auch kein Punkt bis zum
    //nächsten Backslash.
    if( ExtensionIsNotAlreadyIncluded(
        vecStrExcludeFileExtensionsFromCopying,
        strLastExtension )
      )
      vecStrExcludeFileExtensionsFromCopying.push_back(
        strLastExtension);
  }
#ifdef _DEBUG
  for(int i=0;i<(int)vecStrExcludeFileExtensionsFromCopying.size();i++)
    TRACE("vecStrExcludeFileExtensionsFromCopying.at(i): %s\n",
    vecStrExcludeFileExtensionsFromCopying.at(i));
#endif
  return vecStrExcludeFileExtensionsFromCopying;
}

/*bool VectorAlreadyContains(std::vector<CString> &
  rcvecStrFileExtensions,
  CString & strFileExtension)
{
  bool bVectorAlreadyContains=false;

  return bVectorAlreadyContains;
}*/

std::vector<CString> * GetStringVectorOfExtensions(
  const CString & str)
{
  bool bFirstColon = true;
  CString strFileExtension;
  int wRun = 0 ;
  std::vector<CString> *pvecStrFileExtensions;
  //auf MAXWORD setzen, damit das mit dem String extrahieren
  //bei beiden Bendigungen klappt und Quellcode nicht komplexer
  //(mehr Verzweigungen) wird: wenn plus 1, dann ist der Wert "0"
  //durch Werte-Überlauf
  WORD wIndexOfPreviousColon = MAXWORD;
  pvecStrFileExtensions = new std::vector<CString>;
  //TRACE("MAXWORD: %u\n",MAXWORD);
  for(; wRun < str.GetLength(); ++ wRun )
  {
    if( //str[ //(std::basic_string::size_type)
        //wRun]
        str.GetAt(wRun) == ',' )
    {
      //alles als Dateiendung erlauben(auch leere Zeichenkette)
      WORD wIndexOfFirstCharOfCurrentExtension =
        (WORD)(wIndexOfPreviousColon + 1 );
      //zwischen diesem und dem vorgerigen Komma/dem Anfang
      //der Zeichenkette muss
      //mindestens 1 Zeichen au�er eines Kommas liegen
      //if(bFirstColon && wRun>0 || !bFirstColon &&
      //  wIndexOfFirstCharOfCurrentExtension<wRun)
      {
        //++wNumberOfExtensions;
        strFileExtension=str.Mid(wIndexOfFirstCharOfCurrentExtension,wRun-
          wIndexOfFirstCharOfCurrentExtension);
        if(strFileExtension=="*")
        {
          //eventuell schoin enthaltene Dateiendungen l�schen
          pvecStrFileExtensions->clear();
          pvecStrFileExtensions->push_back(strFileExtension);
          //da das Sternchen f�r die Menge aller m�glichen
          //Dateiendungen steht, ist das das Maximum, also
          //muss nicht weiter gepr�ft werden:
          break;
        }
        //wenn die Endung bereits vorkommt in Vektor, nicht nochmal
        //speichern! das w�rde dann im Betrieb(beim Vergleich
        //der Dateiendungen) nur unn�tig Laufzeit
        //kosten
        //if(!VectorAlreadyContains(pvecStrFileExtensions,
        //  strFileExtension)
        if(ExtensionIsNotAlreadyIncluded(*pvecStrFileExtensions,
          strFileExtension))
          pvecStrFileExtensions->push_back(
            strFileExtension);
      }
      if(bFirstColon)
        bFirstColon = false;
      wIndexOfPreviousColon = wRun;
    }
  }
  WORD wIndexOfFirstCharOfCurrentExtension=
    (WORD)(wIndexOfPreviousColon + 1);
  strFileExtension=str.Mid(wIndexOfFirstCharOfCurrentExtension,
    wRun-wIndexOfFirstCharOfCurrentExtension);
  //zwischen diesem und dem vorgerigen Komma/dem Anfang
  //der Zeichenkette muss
  //mindestens 1 Zeichen au�er eines Kommas liegen
  //if(bFirstColon && wRun>0 || !bFirstColon &&
  //  wIndexOfFirstCharOfCurrentExtension<wRun)
  {
    //++wNumberOfExtensions;
    if(ExtensionIsNotAlreadyIncluded(*pvecStrFileExtensions,
      strFileExtension))
      pvecStrFileExtensions->push_back(
        str.Mid(wIndexOfFirstCharOfCurrentExtension,wRun-
        wIndexOfFirstCharOfCurrentExtension));
  }
#ifdef _DEBUG
  for(int i=0;i<(int)pvecStrFileExtensions->size();i++)
    TRACE("pvecStrFileExtensions->at(i): %s\n",
    pvecStrFileExtensions->at(i));
#endif
  return pvecStrFileExtensions;
}

bool IsDriveName(const CString & crstrFullPath)
{
  bool bIsDriveName=false;
  if(crstrFullPath.GetLength()>1)
  {
    TCHAR chFirstChar;
    chFirstChar = crstrFullPath.GetAt(0);
    if( chFirstChar >= 'A' && chFirstChar <= 'Z' &&
      crstrFullPath.GetAt(1) == ':' //&&
      //crstrFullPath.GetAt(2)=='\\'
      )
      bIsDriveName = true;
  }
  return bIsDriveName;
}
CString GetDriveNameOrShareName(const CString & crstrFullPath)
{
  CString strDriveNameOrShareName;
  if( IsDriveName(crstrFullPath) )
    return //strDriveNameOrShareName=
      crstrFullPath.Left(3);
  else
    //Wenn 1 Backslash, ...
    if( crstrFullPath.Left(2) == "\\" )
      //...dann ist das Laufwerk unbestimmt ("USB-Stick") und muss erst
      //ausgewählt werden.
      return strDriveNameOrShareName;
  return crstrFullPath;
}
