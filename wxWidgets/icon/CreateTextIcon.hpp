/*
 * CreateTextIcon.hpp
 *
 *  Created on: Nov 22, 2010
 *      Author: Stefan
 */

#ifndef CREATETEXTICON_HPP_
#define CREATETEXTICON_HPP_

//Forward declarations.
class wxColour;
class wxIcon ;
class wxString ;

void CreateTextIcon( wxIcon & icon, const wxString & r_wxstr ) ;
void CreateTextIcon( wxIcon & icon, const wxString & r_wxstr, const wxColour & ) ;
void CreateWhiteTextIcon( wxIcon & icon, const wxString & r_wxstr ) ;

#endif /* CREATETEXTICON_HPP_ */
