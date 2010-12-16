/*
 * URL.hpp
 *
 *  Created on: Nov 13, 2010
 *      Author: Stefan
 */

#ifndef URL_HPP_
#define URL_HPP_

#ifndef _MSC_VER // no MicroSoft compiler
  #include <Controller/character_string/MFC_Compatibility/CString.hpp>
  using namespace MFC_Compatibility ;
#endif

//Um das Passwort eines Zielverzeichnis, das auf einem FTP-Server liegt,
//zu verstecken. Often it is unwanted for the user that this password is
//shown on the display.
CString PossiblyHidePassword(
  const CString & cr_strOrginalDestinationPath//,
  ) ;

#endif /* URL_HPP_ */
