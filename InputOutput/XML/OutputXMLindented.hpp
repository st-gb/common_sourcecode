#pragma once

#include <ostream> //class std::ostream

void OutputXMLindented(const char * p_chXML, std::ostream & r_std_ostream)
{
  char ch = * p_chXML;
  unsigned uiIndention = 0;
  bool bOpeningBracket = false;
  while(ch)
  {
    r_std_ostream << ch;
    switch( ch)
    {
    case '<':
      {
      bOpeningBracket = true;
      }
      break;
    case '>':
      r_std_ostream << "\n";
      {
      unsigned ui = uiIndention;
      while(ui --)
        r_std_ostream << " ";
      }
      break;
    case '/':
      if( uiIndention > 0 && bOpeningBracket) //previous char was '<'
      {
        -- uiIndention;
        bOpeningBracket = false;
      }
      break;
    default:
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
