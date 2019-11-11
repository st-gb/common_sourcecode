#include <Windows.h> //::MultiByteToWideChar(...)

#ifdef _MSC_VER //MS compiler
LPCSTR UTF8toASCII(const char * str)
{
  LPWSTR pwstrTranslation = NULL;

  int nNumberOfRequiredWideCharacters = ::MultiByteToWideChar(
    CP_UTF8,         // code page
    0,         // character-type options
    //str.c_str(), // string to map
    str,
    -1,       // number of bytes in string
    NULL,  // wide-character buffer
    0        // size of buffer
    );
  LOGN("28.05.2008 21.50.08 " << nNumberOfRequiredWideCharacters);
  if(nNumberOfRequiredWideCharacters)
  {
    pwstrTranslation = new WCHAR[nNumberOfRequiredWideCharacters];
    if(pwstrTranslation)
    {
      ::MultiByteToWideChar(
        CP_UTF8,         // code page
        0,         // character-type options
        //str.c_str(), // string to map
        str,
        -1,       // number of bytes in string
        pwstrTranslation,  // wide-character buffer
        nNumberOfRequiredWideCharacters        // size of buffer
        );
    #ifdef _LOG
      BYTE byWideCharByte;
      for(DWORD i = 0 ; i < wcslen(pwstrTranslation) ; ++ i )
      {
        byWideCharByte = * (pwstrTranslation + i);
        LOG(byWideCharByte << "(" << (int) byWideCharByte << ")" );
        byWideCharByte = * ( (BYTE * ) (pwstrTranslation + i ) + 1 );
        LOG(byWideCharByte << "(" << (int) byWideCharByte << ")" );
      }
    #endif
      //Newline erzwingen.
      LOGN("");
      LOGN("28.05.2008 22.03.41");
      //When using an ATL string conversion macro, specify the USES_CONVERSION
      //macro at the beginning of your function in order to avoid compiler errors.
      USES_CONVERSION;
      //LPCSTR pszA =W2A(pwstrTranslation);
      //Use an object that is created on the heap rather than a stack object. So
      //its contents aren't freed after leaving the scope where it was declared.
      CW2A * pw2a = new CW2A(pwstrTranslation);
      LPCSTR pszA = pw2a->m_psz;
      LOGN("28.05.2008 22.03.52 " << strlen(pszA) );
      LOGN(pszA);
      for(DWORD i = 0 ; i < strlen(pszA); ++ i )
      {
        LOG( * (pszA + i) << "(" << (int) *(pszA + i ) << ")" );
      }
      //Newline erzwingen.
      //LOGN((unsigned long)pszA<<pszA<<"");
      delete [] pwstrTranslation;
      return pszA;
    }
  }
  //Error.
  //else
    return NULL;
}
#endif //#ifdef _MSC_VER
