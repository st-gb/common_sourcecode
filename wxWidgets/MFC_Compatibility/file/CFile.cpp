/* 
 * File:   CFile.cpp
 * Author: Stefan
 * 
 * Created on 14. September 2009, 12:10
 */

#include <wx/file.h>
#include "CFile.hpp"
#include "CFileException.hpp"
//GetwxString_Inline( LPCSTR )
#include <wxWidgets/Controller/character_string/wxStringHelper.hpp>

using namespace MFC_Compatibility ;

CFile::CFile()
{

}

CFile::CFile(const CFile& orig) {
}

CFile::~CFile() {
}

inline //virtual
  ULONGLONG CFile::GetLength() const
{
  return Length() ;
}

inline //virtual
  //see http://msdn.microsoft.com/de-de/library/hwbccf8z%28VS.80%29.aspx:
  BOOL CFile::Open(
   LPCTSTR lpszFileName,
   UINT uintOpenFlags,
   CFileException * pError //= NULL
  )
{
  wxString wxstrFileName(lpszFileName) ;
  wxFile::OpenMode wxfile_openmode = GetOpenMode(uintOpenFlags) ;
  return
    //http://docs.wxwidgets.org/2.8/wx_wxfile.html#wxfileopen:
    //"Opens the file, returning true if successful."
    wxFile::Open( //lpszFileName
    wxstrFileName, wxfile_openmode ) ;
//  return false ;
}

//If Unicode then TCHAR->WCHAR, so we can also declare/ define an explicitely
// "char" version.
#if defined( _UNICODE) || defined(UNICODE)
inline //virtual
  //see http://msdn.microsoft.com/de-de/library/hwbccf8z%28VS.80%29.aspx:
  BOOL CFile::Open(
   LPCSTR lpcstrFileName,
   UINT uintOpenFlags,
   CFileException * pError //= NULL
  )
{
  wxFile::OpenMode wxfile_openmode = GetOpenMode(uintOpenFlags) ;
  return wxFile::
    //http://docs.wxwidgets.org/trunk/classwx_file.html
    // #70f2abe0e310dcf77ea6aeaac60df25b:
    // "Opens the file, returning true if successful."
    Open( wxWidgets::GetwxString_Inline( lpcstrFileName ), wxfile_openmode ) ;
//  return false ;
}
#endif //#if defined( _UNICODE) || defined(UNICODE)
