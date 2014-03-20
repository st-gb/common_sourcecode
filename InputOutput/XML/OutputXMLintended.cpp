/*
 * OutputXMLintended.cpp
 *
 *  Created on: 01.03.2014
 *      Author: mr.sys
 */

#include "OutputXMLindented_inl.hpp"

/** Because of outputting to a std::ostream (ANSI char streams) you may need
 *  to set the locale before calling this function. */
void OutputXMLindented(
  const char * p_chXML,
  std::ostream & r_std_ostream,
  //from http://www.cantrip.org/locale.html
  std::locale locale = std::locale("")
  )
{
  OutputXMLindented_inl(p_chXML, r_std_ostream, locale);
}
