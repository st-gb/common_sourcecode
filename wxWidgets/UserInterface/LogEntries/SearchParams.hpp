/* 
 * File:   SearchParams.hpp
 * Author: mr.sys
 *
 * Created on 10. Juni 2015, 22:17
 */

#ifndef SEARCHPARAMS_HPP
#define	SEARCHPARAMS_HPP

class SearchParams
{
  bool m_searchInMessage;
  bool m_searchInFunctionName;
  wxString m_searchString;
public:
  SearchParams() : 
    m_searchInMessage(true), 
    m_searchInFunctionName(false) 
    { }
  bool IsSearchedInMessage() const { return m_searchInMessage; } 
  bool IsSearchedInFunctionName() const { return m_searchInFunctionName; }
  wxString GetSearchString() const { return m_searchString; }
  
  void SetSearchString(const wxString & value ) { m_searchString = value; }
  void SetSearchInMessage(const bool b ) { m_searchInMessage = b; }
  void SetSearchInFunctionName(const bool b ) { m_searchInFunctionName = b; }
};
    
#endif	/* SEARCHPARAMS_HPP */

