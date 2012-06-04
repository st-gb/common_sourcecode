/*
 * ConvertXercesStringToStdWstring.cpp
 *
 *  Created on: 13.05.2012
 *      Author: Stefan
 */

#include "ConvertXercesStringToStdWstring.hpp"

std::wstring Xerces::ConvertXercesStringToStdWstring(
  const XMLCh * cpc_xmlch
  )
{
  return Xerces::ConvertXercesStringToStdWstring_inline(cpc_xmlch);
}
