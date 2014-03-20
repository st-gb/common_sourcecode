/*
 * OutputXMLindented_inl.hpp
 *
 *  Created on: 07.03.2014
 *      Author: mr.sys
 */

#ifndef OUTPUTXMLINDENTED_INL_HPP_
#define OUTPUTXMLINDENTED_INL_HPP_

#include <ostream> //class std::ostream
#include <ctype.h> //iswspace(...)
#include <locale>    /* for std::locale */

/** Because of outputting to a std::ostream (ANSI char streams) you may need
 *  to set the locale before calling this function. */
void OutputXMLindented_inl(
  const char * p_chXML,
  std::ostream & r_std_ostream,
  //from http://www.cantrip.org/locale.html
  std::locale locale = std::locale("")
  )
{
  char ch = * p_chXML;
  unsigned uiIndention = 0;
  bool bOpeningBracket = false;
  bool bSlash = false;
  r_std_ostream.imbue(locale);
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

#endif /* OUTPUTXMLINDENTED_INL_HPP_ */
