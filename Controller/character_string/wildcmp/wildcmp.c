#include <winnt.h> //for STDAPICALLTYPE
#include <ctype.h> //_toupper(...)

//Dieser Quellcode stammt von Wes Jones ? bzw. dessen DirectoryChangesW-
//Wrapper?
BOOL STDAPICALLTYPE wildcmp(LPCTSTR string, LPCTSTR wild )
{
  const TCHAR * cp, * mp;
  cp = mp = NULL;

  //Wenn nicht das Ende von "string" und das aktuelle Zeichen bei "wild"
  //nicht der kleenische Sternoperator/ das Sternchen ist.
  while ( ( * string) && ( * wild != _T('*') ) )
  {
    //Wenn die Groß- und Kleinschreibung ignoriert wird und die Zeichen
    //ungleich sind und das aktuelle Zeichen bei wild
    //nicht das Frage-/Joker-Zeichen ist...
    if( ( _toupper( * wild) != _toupper( * string) ) && ( * wild != _T('?') ) )
    {
      //...dann passt das Suchmuster "wild" nicht auf "string"
      return FALSE;
    }
    wild ++; //Advance by 1 character.
    string ++; //Advance by 1 character.
  }
  //Solange nicht das String-Ende-Zeichen ('\0').
  while( * string)
  {
    if ( * wild == _T('*') )
    {
      //If the next character is the string termination ('\0') character.
      if( ! * ++ wild )
      {
        return TRUE;
      }
      mp = wild;
      cp = string + 1;
    }
    else
      //If the current characters are case-INsensitively identical or the
      //current character is a joker (-> may be ANY character) character.
      if( ( _toupper( * wild) == _toupper( * string) ) || ( * wild == _T('?') )
        )
      {
        wild ++; //Advance by 1 character.
        string ++; //Advance by 1 character.
      }
      else
      {
        wild = mp;
        string = cp ++;
      }
  }
  //As long as the star character (´-> Kleene star operator).
  while ( * wild == _T('*') )
  {
    wild ++; //Advance by 1 character.
  }
  //If the '\0' char (string end) is reached, return "TRUE".
  return ( ! * wild ) ? TRUE : FALSE;
}
