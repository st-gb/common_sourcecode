/* 
 * File:   CFile.hpp
 * Author: Stefan
 *
 * Created on 14. September 2009, 12:10
 */

#ifndef _CFILE_HPP
#define	_CFILE_HPP

#include <wx/file.h>
#include <windef.h> //BOOL
#include <windows.h> //ULONGLONG

//class CFileException ;
#include "CFileException.hpp"

namespace MFC_Compatibility
{
  //This class emulates MFC CFile by using a wxFile derived class
  class CFile
    : public wxFile
  {
  public:
    //same as CFile, copied from include/afx.h
	enum OpenFlags {
		modeRead =         (int) 0x00000,
		modeWrite =        (int) 0x00001,
		modeReadWrite =    (int) 0x00002,
		shareCompat =      (int) 0x00000,
		shareExclusive =   (int) 0x00010,
		shareDenyWrite =   (int) 0x00020,
		shareDenyRead =    (int) 0x00030,
		shareDenyNone =    (int) 0x00040,
		modeNoInherit =    (int) 0x00080,
		modeCreate =       (int) 0x01000,
		modeNoTruncate =   (int) 0x02000,
		typeText =         (int) 0x04000, // typeText and typeBinary are
		typeBinary =       (int) 0x08000, // used in derived classes only
		osNoBuffer =       (int) 0x10000,
		osWriteThrough =   (int) 0x20000,
		osRandomAccess =   (int) 0x40000,
		osSequentialScan = (int) 0x80000,
		};

  CFile();
  CFile(const CFile& orig);
  virtual ~CFile();
  virtual ULONGLONG GetLength() const ;
  static wxFile::OpenMode GetOpenMode(UINT nOpenFlags)
  {
    wxFile::OpenMode wxfile_openmode =
      //Avoid the variable being uninitialized.
      wxFile::read ;
    if( nOpenFlags & modeRead )
    {
      wxfile_openmode = wxFile::read ;
    }
    if( nOpenFlags & modeReadWrite )
    {
      wxfile_openmode = wxFile::read_write ;
    }
//    if( nOpenFlags & shareDenyWrite )
//    {
//      wxfile_openmode = wxFile::write_excl ;
//    }
    return wxfile_openmode ;
  }

  virtual BOOL Open(
     LPCTSTR lpszFileName,
     UINT nOpenFlags,
     CFileException * pError = NULL
    );
  virtual BOOL Open(
    LPCSTR lpcstrFileName,
    UINT nOpenFlags,
    CFileException * pError = NULL
    );
  ULONGLONG Seek(LONGLONG ll)
  {
    //http://docs.wxwidgets.org/trunk/classwx_file.html
    // #106441378d84369853a60b0c8846aa9a
    //"Returns:
    // The actual offset position achieved, or wxInvalidOffset on failure."
    wxFileOffset wxfileoffset = wxFile::Seek(ll,wxFromStart) ;
    if( wxfileoffset == wxInvalidOffset )
      //see http://msdn.microsoft.com/de-de/library/8c5ccz0x%28VS.80%29.aspx:
      //"If the requested position is legal, Seek returns the new byte offset
      //from the beginning of the file. Otherwise, the return value is
      //undefined and a CFileException object is thrown."
      throw CFileException() ;
    return wxfileoffset ;
  }
  //http://msdn.microsoft.com/en-us/library/t68z1bx0%28VS.80%29.aspx
  ULONGLONG SeekToEnd( )
  {
    return SeekEnd() ;
  }
  private:
  };
};

#endif	/* _CFILE_HPP */

