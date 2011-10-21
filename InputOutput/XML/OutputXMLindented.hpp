#pragma once

#include <ostream> //class std::ostream
#include <ctype.h> //iswspace(...)

inline void OutputXMLindented(const char * p_chXML, std::ostream & r_std_ostream)
{
  char ch = * p_chXML;
  unsigned uiIndention = 0;
  bool bOpeningBracket = false;
  bool bSlash = false;
  while(ch)
  {
    r_std_ostream << ch;
    switch( ch)
    {
    case '<':
      bSlash = false;
      {
      bOpeningBracket = true;
      }
      break;
    case '>':
      r_std_ostream << "\n";
      if( bSlash ) //Slash before this '>'.
      {
        -- uiIndention; //Undo the incrementation of the # of indentation ' '.
        bSlash = false;
      }
      {
        unsigned ui = uiIndention;
        while(ui --)
          r_std_ostream << " ";
      }
      break;
    case '/':
      bSlash = true;
      if( uiIndention > 0 && bOpeningBracket) //previous char was '<'
      {
        -- uiIndention;
        bOpeningBracket = false;
      }
      break;
    default:
      if( ! ::iswspace(ch) )
        bSlash = false;
      if( bOpeningBracket ) //previous char was '<'
      {
        ++ uiIndention;
        bOpeningBracket = false;
      }
      break;
    }
    ++ p_chXML;
    ch = * p_chXML;
  }
}
