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
#include "CCriticalSection.hpp"

namespace MFC_Compatibility
{
  //For code compatibility: Does the same as MFC's 
  //CSingleLock class, but is for
  class CSingleLock
  {
  private:
    //wxCriticalSection * mp_wxcs ;
      MFC_Compatibility::CCriticalSection * mp_ccriticalsection ;
  public:
    //inline 
      CSingleLock(
        //wxCriticalSection & r_wxcs,
        MFC_Compatibility::CCriticalSection * p_criticalsection ,
        BOOL bInitialLock = FALSE )
    {
      mp_ccriticalsection = p_criticalsection ;
      if(bInitialLock)
        //r_wxcs.Enter();
        mp_ccriticalsection->Lock() ;
      //mp_wxcs = & r_wxcs ;
    }
    ~CSingleLock()
    {
//      LOGN("~CSingleLock")
      mp_ccriticalsection->Unlock() ;
    }
    //CSingleLock

    //MFC Library Reference  CSingleLock::Lock :
    //Nonzero if the function was successful; otherwise 0.
    inline BOOL Lock(
      //DWORD dwTimeOut = INFINITE 
      )
    {
      //wxcs.Enter() ;
      //mp_wxcs->Enter() ;
      mp_ccriticalsection->Lock() ;
      return TRUE ;
    }

    //MFC Library Reference  CSingleLock::Unlock:
    //"Nonzero if the function was successful; otherwise 0."
    inline BOOL Unlock( )
    {
      //wxcs.Leave() ;
      //mp_wxcs->Leave() ;
      mp_ccriticalsection->Unlock() ;
      return TRUE ;
    }
  };
};
