#pragma once
#ifndef OUTPUT_XML_INTEDED_HPP
#define OUTPUT_XML_INTEDED_HPP

#include <ostream> //class std::ostream
#include <locale>    /* for std::locale */

/** Because of outputting to a std::ostream (ANSI char streams) you may need
 *  to set the locale before calling this function. */
void OutputXMLindented(
  const char * p_chXML,
  std::ostream & r_std_ostream,
  //from http://www.cantrip.org/locale.html
  std::locale locale = std::locale("")
  );

#endif //OUTPUT_XML_INTEDED_HPP
