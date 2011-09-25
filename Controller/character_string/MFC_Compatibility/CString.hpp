#pragma once
/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
//#include <string>
//This MFC CString emulation class is also (Linux) g++ compiler compatible
//#include <StdString.h>
#include <string> //class std::string
//#include <windows.h> //LPCSTR
//#include <winnt.h> //TCHAR
#include <tchar.h> //TCHAR
#include <Controller/character_string/stdtstr.hpp> //GetStdString_Inline(...)
#include <preprocessor_macros/string_typedefs.h> //LPCTSTR
#include <string.h>

namespace MFC_Compatibility
{
//  class CString ;
//  std::string::operator CString() const ;
  //  typedef CStdStr CString ;
  class CString
//    : public std::string
    //"TCHAR": "wchar_t" (16 bit) if "UNICODE", else "char" (8 bit)
    : public std::basic_string<TCHAR>
  {
  public:
    //Implementing an empty constructor is needed because there is also a
    //parameterized c'tor.
    CString()
    {
    }
//    CString(char ch) //Implement MFC's "CString(char)"
    CString(TCHAR tch) //Implement MFC's "CString(char)"
      :
      //Because there is no std::string(char) use the c'tor
      // "std::string(int,char)"
//      std::string( 1, ch)
    std::basic_string<TCHAR>( 1, tch)
    {
    }
//    CString(char * p_ch) //Implement MFC's "CString(char)"
    CString(TCHAR * p_tch) //Implement MFC's "CString(char)"
      :
      //Because there is no std::string(char) use the c'tor
      // "std::string(int,char)"
//      std::string( p_ch)
      std::basic_string<TCHAR>( p_tch)
    {
    }
//    CString(const char * p_ch, int num) //Implement MFC's "CString(char)"
    CString(const TCHAR * p_tch, int num) //Implement MFC's "CString(char)"
      :
      //Because there is no std::string(char) use the c'tor
      // "std::string(int,char)"
//      std::string( p_ch, num)
      std::basic_string<TCHAR>( p_tch, num)
    {
    }
    //Constructor to solve cast to CString from std::string in
    // "method Left(unsigned short wNumChars)"
    //idea from:
    //  http://efreedom.com/Question/1-3046463/Non-Scalar-Type-Requested
    // (constructor with parameter data type of base class):
//    CString(std::string stdstr )
    CString(std::basic_string<TCHAR> stdtstr )
    {
//      * this = stdstr ;
      clear() ;
//      append( stdstr.c_str() ) ;
      append( stdtstr.c_str() ) ;
    }
    bool IsEmpty() const
    {
      return empty() ;
    }
    //see http://msdn.microsoft.com/en-us/library/aa314315%28VS.60%29.aspx
    int CompareNoCase( //const CString & cr_str
//      const char * const cpc_ch)
      const TCHAR * const cpc_tch)
    {
      #ifdef UNICODE
      return
        //http://msdn.microsoft.com/en-us/library/k59z8dwe%28v=vs.80%29.aspx:
        //"Perform a lowercase comparison of strings."
        _wcsicmp( c_str(), //cr_str.c_str()
          cpc_tch ) ;
      #else //#ifdef UNICODE
      return
          //http://msdn.microsoft.com/en-us/library/k59z8dwe%28v=vs.80%29.aspx:
          //"Perform a lowercase comparison of strings."
        stricmp( c_str(), //cr_str.c_str()
//          cpc_ch ) ;
          cpc_tch ) ;
      #endif //#ifdef UNICODE
    }
#ifdef UNICODE //-> compare a "wchar_t" array with a "char" array.
    //see http://msdn.microsoft.com/en-us/library/aa314315%28VS.60%29.aspx
    int CompareNoCase( //const CString & cr_str
      const char * const cpc_ch)
    {
      //      CString
      //      char * ar_ch = new char( size()
      //        //+1 char for term. 0 char
      //        + 1 ) ;
      //      tolower( ar_ch) ;
      //      c_str() ;
      const wchar_t * cp_wch = c_str() ;
      wchar_t wch = * cp_wch ;
      char ch = * cpc_ch ;
      unsigned short index = 1 ;
      //While NOT string terminating "0" char.
      while( wch && ch)
      {
        wch = towlower( wch) ;
        ch = tolower(ch) ;
        if( wch < ch )
          return -1 ;
        else if( wch > ch )
          return 1 ;
        wch = * ( cp_wch + index ) ;
        ch = * ( cpc_ch + index ) ;
        ++ index ;
      }
      if( ! wch )
      {
        if( ! ch)
          return 0 ;
        //string < compare string
        else return - 1 ;
      }
      else
        return 1 ;
    }
#endif
    //see http://msdn.microsoft.com/ja-jp/library/ms928979.aspx:
    //"Returns the length of the changed string."
    int Delete(int nIndexOf1stCharToDelete, int nNumberOfCharactersToRemove = 1)
    {
      erase(nIndexOf1stCharToDelete,nNumberOfCharactersToRemove) ;
      return length() ;
    }
    int Find(char ch, int nStart = 0) const
    {
      return find(ch, nStart) ;
    }
    //see http://msdn.microsoft.com/en-us/library/aa314338%28VS.60%29.aspx:
//    char GetAt(int pos) const
    TCHAR GetAt(//int pos
      //Use same type as size() returns to avoid g++ warning
      //"comparison between signed and unsigned integer expressions"
      size_type pos) const
    {
      if( pos >= 0 && pos < size() )
//        return * this [pos] ;
        return at(pos) ;
      else
        return 0 ;
    }
//    const char * GetBuffer() const
    const TCHAR * GetBuffer() const
    {
      return c_str() ;
    }
    int GetLength() const
    {
      return length() ;
    }
    //see http://msdn.microsoft.com/ja-jp/library/ms928946.aspx:
    //"Returns the length of the changed string."
//    int Insert(int nCharIndexDirectlyRightOfInsertion, LPCSTR lpcstr)
    int Insert(int nCharIndexDirectlyRightOfInsertion, LPCTSTR lpctstr)
    {
//      insert(nCharIndexDirectlyRightOfInsertion,lpcstr) ;
      insert(nCharIndexDirectlyRightOfInsertion,lpctstr) ;
      return length() ;
    }
    CString Left(unsigned short wNumChars) const
    {
      return //(const CString &)
//        static_cast<CString> ( substr(0, wNumChars) ) ;
        CString( substr(0, wNumChars) ) ;
    }
    //Conversion
    operator LPCSTR() const
    {
      return GetStdString_Inline( * this).c_str() ;
    }
    operator LPCTSTR() const
    {
      return c_str() ;
    }
    //Conversion
//    operator const CHAR * ()
    operator const TCHAR * ()
    {
      return c_str() ;
    }
//    bool operator != ( const CString & cr_str ) const
//    {
//      return
//    }
//    char operator [] ( unsigned short usIndex ) const
    TCHAR operator [] ( unsigned short usIndex ) const
    {
//      return (char)* this [usIndex] ;
      //using "reference" is from:
      //http://msdn.microsoft.com/en-us/library/dba41a1z.aspx
//      std::basic_string <TCHAR>::const_reference stdtstr_ref =
        //If no cast to "(const TCHAR *)":
        //"Multiple markers at this line - ambiguous overload for 'operator*'
        //in '**((+(((unsigned int)usIndex) * 4u)) +
        //((const MFC_Compatibility::CString*)this))' - candidates are:
        //operator*(const TCHAR*) - operator*(const CHAR*)"
//        (TCHAR)
        //( * this [usIndex] ) ;
          return
//              std::basic_string<TCHAR>::operator [usIndex] ;
//          ( (std::basic_string<TCHAR>)this ) [usIndex] ;
          at(usIndex) ;
//      return stdtstr_ref ;
    }
//    CString operator + ( const TCHAR * ar_tch ) const
//    {
////      std::string stdstr(ch,1) ;
////      CString cstring(ch) ;
//      CString cstring(ar_tch) ;
//      return cstring.append(ar_tch) //stdstr ;
//        ;
//    }
//    bool operator != ( const char ch ) const
    bool operator != ( const TCHAR tch ) const
    {
//      std::string stdstr(ch,1) ;
//      CString cstring(ch) ;
      CString cstring(tch) ;
      return * this != //stdstr ;
        cstring ;
    }
    //see http://msdn.microsoft.com/ja-jp/library/ms928955.aspx:
    CString Mid(int nIndexOfFirstChar, int nCount) const
    {
      return static_cast<CString> ( substr( nIndexOfFirstChar, nCount ) ) ;
    }
    int ReverseFind(char ch) const
    {
      //http://www.cplusplus.com/reference/string/string/rfind/:
      //"The position of the last occurrence in the string of the searched content.
      //If the content is not found, the member value npos is returned."
      return rfind(ch) ;
    }
    CString Right( unsigned short wNumChars) const
    {
      size_type length = //length() ;
        size() ;
      return //(const CString &)
        static_cast<CString> ( substr(length - wNumChars,wNumChars) ) ;
    }
//    CString Tokenize( char * p_ch, int & r_nCurrentPos) const
    CString Tokenize( TCHAR * p_tch, int & r_nCurrentPos
//      //Use same type as size() returns to avoid g++ warning
//      //"comparison between signed and unsigned integer expressions"
//      size_type & r_nCurrentPos
      ) const
    {
      CString cstringToken ;
      if( //Cast same to type as size() returns to avoid g++ warning
          //"comparison between signed and unsigned integer expressions"
          (std::basic_string<TCHAR>::size_type) r_nCurrentPos < size() )
      {
//        std::string stdstrTokenizers(p_ch) ;
        std::basic_string<TCHAR> stdtstrTokenizers(p_tch) ;
        bool bTokenizerFound = false ;
//        const char * cp_chCurrentCharacter =
        const TCHAR * cp_tchCurrentCharacter =
          //Set to "r_nCurrentPos"th character.
          c_str() + r_nCurrentPos ;
        while( // <=> cp_chCurrentCharacter <> '\0'
//            * cp_chCurrentCharacter )
          * cp_tchCurrentCharacter )
        {
//          std::size_t stdsize_tIndexOfFirstOccurence = stdstrTokenizers.find(
          std::size_t stdsize_tIndexOfFirstOccurence = stdtstrTokenizers.find(
//            * cp_chCurrentCharacter,
            * cp_tchCurrentCharacter,
            r_nCurrentPos ) ;
          if( stdsize_tIndexOfFirstOccurence != npos )
          {
            cstringToken = substr( r_nCurrentPos ,
              //# chars
//              ( cp_chCurrentCharacter - c_str() ) - 1 - r_nCurrentPos
              ( cp_tchCurrentCharacter - c_str() ) - 1 - r_nCurrentPos
              ) ;
            //Current char index.
//            r_nCurrentPos = cp_chCurrentCharacter - c_str() ;
            r_nCurrentPos = cp_tchCurrentCharacter - c_str() ;
            bTokenizerFound = true ;
            break ;
          }
//          ++ cp_chCurrentCharacter ;
          ++ cp_tchCurrentCharacter ;
        }
        if( ! bTokenizerFound )
          r_nCurrentPos = -1 ;
      }
      return cstringToken ;
    }
  };
//  operator std::string::CString() const
//  {
//    return c_str() ;
//  }
};

////For "TCHAR * " + "CString object"
//MFC_Compatibility::CString operator + ( const TCHAR * ar_tch ,
//  const MFC_Compatibility::CString & cr_cstringRight)
//{
////      std::string stdstr(ch,1) ;
////      CString cstring(ch) ;
//  MFC_Compatibility::CString cstring(ar_tch) ;
//  return cstring.append( cr_cstringRight )//stdstr ;
//    ;
//}
