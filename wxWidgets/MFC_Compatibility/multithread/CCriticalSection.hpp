#pragma once //incl. guard

//wenn fatal error C1010: Unerwartetes Dateiende waehrend 
//der Suche nach der Direktive fuer die vorkompilierte Header-Datei
//dann Pfad ändern von "stdafx.h"
//durch irgendeinem Grund muss man für die "Release"-Version
//auf den physischen Pfad verweisen für include-files:
//#include "..\stdafx.h"
//und bei der Debug-Version ist das falsch und man muss den
//Pfad unabhängig vom Verzeichnis, in dem er sich befindet
//angeben:
#include "stdafx.h" //for "BOOL" etc.
#include <wx/thread.h> //for wxCriticalSection
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)

typedef int BOOL ;

namespace MFC_Compatibility
{
//For code compatibility: Does the same as MFC's 
//CSingleLock class, but is for
class CCriticalSection
    : public wxCriticalSection
{
private:
//  wxCriticalSection * mp_wxcs ;
public:
  //inline CCriticalSection()
  //{
  //  if(bInitialLock)
  //    wxcs.Enter();
  //  mp_wxcs = & r_wxcs ;
  //}
  //CSingleLock

  //Make the methods inline to execute faster. So they need to be defined in
  // the include file (= in _this_ class )
  //MFC's CCriticalSection::Lock : 
  //"Nonzero if the function was successful; otherwise 0."
  inline BOOL Lock(
    //DWORD dwTimeOut = INFINITE 
    )
  {
//    LOGN("CCriticalSection::Lock before wxCriticalSection::Enter()")
    Enter() ;
//    LOGN("CCriticalSection::Lock after wxCriticalSection::Enter()")
    return TRUE ;
  }

  //MFC's CCriticalSection::Unlock:
  //Nonzero if the CCriticalSection object was owned by the thread and the 
  //release was successful; otherwise 0.
  inline BOOL Unlock( )
  {
//    LOGN("CCriticalSection::Unlock before wxCriticalSection::Leave()")
    Leave() ;
//    LOGN("CCriticalSection::Unlock after wxCriticalSection::Leave()")
    return TRUE;
  }
};
};
