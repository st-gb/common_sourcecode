/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * css_basic_stringstream.hpp
 *
 *  Created on: 11.06.2011
 *      Author: Stefan
 *  class for enabling "char *" and "std::string" output for
 *  "class std::basic_stringstream <wchar_t>" (class "std::wstringstream")
 */

#ifndef CSS_BASIC_STRINGSTREAM_HPP_
#define CSS_BASIC_STRINGSTREAM_HPP_

#include <sstream> //class std::basic_stringstream
#include "logging_preprocessor_macros_definitions.h" //
#include <Controller/character_string/getUTF8string.hpp> //getUTF8string(...)

namespace css
{
//public:
  typedef LOGGING_CHARACTER_TYPE loggingCharacterType;
  //std::wstringstream has no operator << (std::string)
  template <typename _CharT> //, typename _Traits, typename _Alloc>
  class basic_stringstream
    : public std::basic_stringstream <_CharT>//, _Traits, _Alloc>
  {
  public:
    //from class std::basic_stringstream (MinGW gcc 4.5.2 "sstream" file )
    typedef _CharT          char_type;

//      typedef _Traits           traits_type;
    //std::basic_ostream
//      typedef std::basic_ostream<_CharT, _Traits>    __ostream_type;
//      typedef std::basic_ostream<_CharT>    __ostream_type;

    /** Return type for operator << for operands of single byte character type.
    * Must be a type of _this_ class, else following concatenations
    * via "<<" and single byte character are not possible when >>_CharT<<
    * is "wchar_t". */
    typedef css::basic_stringstream<_CharT>    __ostream_type;
//      __ostream_type

    /** Overwrite class std::basic_ostream's << operator because it returns a
    * std::basic_ostream object. but a css::basic_stringstream object is
    * needed. */
    template<typename _ValueT>
      __ostream_type &
      operator <<(_ValueT __v)
    {
      std::basic_stringstream<char_type> std_bss;
      std_bss << __v;
      std_bss.flush();
//        *this << //__v;
//            std_bss.str();
      this->write(std_bss.str().c_str(), std_bss.str().length() );
//        this->write(std_bss.)
      return
        * this;
//          (__ostream_type)
//            //see http://ubuntuforums.org/archive/index.php/t-529935.html:
            //("What's the C++ Equivalent of Java "super" keyword?")
////          ( (std::basic_stringstream<char_type> *) this ) << __v;
////          this.std::basic_stringstream<char_type>).operator <<(__v);
////            this->std::basic_stringstream<char_type>.operator <<(__v);
////            (* this).std::basic_stringstream<char_type>  << __v;
//            std::basic_stringstream<char_type>::operator <<(__v);
//          static_cast<std::basic_stringstream<char_type> *>(this)//->operator <<(__v);
//            << __v;
//        static_cast<std::basic_stringstream<wchar_t> >(*this) << __v;
//          ( std::basic_stringstream<char_type>) (*this) ) << __v;
    }

//      __ostream_type & operator<< (
//          void * p_v)
//      {
//        return *this << p_v;
//      }
//      std::basic_ostream<char_type,traits_type>

    /** Must return an object of _this_ type, else following concatenations
    * via "<<" and are not possible. */
    __ostream_type
    & operator << (
        const char * p_ch)
    {
//        #error "css::basic_stringstream"
      #if __GNUC__ > 3
//        #pragma message("css::basic_stringstream << const char * ")
      #endif //#if __GNUC__ > 3
//        return r_std_str;
      //return _M_insert<std::string>(r_std_str);
      //return

      for(short w = 0; p_ch[w] != '\0'; ++ w)
      {
        put( (char_type) p_ch[w] );
      }
      /** @see ostream.tcc */
      return *this;
    }
    /** Must return an object of _this_ type, else following concatenations
    * via "<<" and are not possible. */
    __ostream_type
    & operator << (
//        const wchar_t * p_ch
        const std::wstring & wstr
        )
    {
//        #error "css::basic_stringstream"
      #if __GNUC__ > 3
//        #pragma message("css::basic_stringstream << const char * ")
      #endif //#if __GNUC__ > 3
//        return r_std_str;
      //return _M_insert<std::string>(r_std_str);
      //return
      std::string std_str;
      getUTF8string_inline(wstr, std_str);
//      for(short w = 0; p_ch[w] != '\0'; ++ w)
//      {
//        put( (char_type) p_ch[w] );
//      }
      /** @see ostream.tcc */
      return //*this;
        //-> use operator with std::string
        *this << std_str;
    }

//      __ostream_type & operator<< (
//          const wchar_t * p_wchar_t)
//      {
////        #error "css::basic_stringstream"
//        #pragma message("css::basic_stringstream << const wchar_t * ")
////        return r_std_str;
//        //return _M_insert<std::string>(r_std_str);
//        //return
//
////        for(short w = 0; p_ch[w] != '\0'; ++ w)
////        {
////          put( (char_type) p_ch[w] );
////        }
////        ostream& operator<< (ostream& out, char c );
//        //see ostream.tcc
//        return *this << p_wchar_t;
//      }

    /**
     * This function is necessary for wchar_t / wide strings to provide
     * output for ANSI char strings.
     */
    __ostream_type & operator << (
        const std::string & r_std_str)
    {
#if __GNUC__ > 3
//      #pragma message("css::basic_stringstream << const std::string & ")
#endif
//        return r_std_str;
      //return _M_insert<std::string>(r_std_str);
      //return
      for(std::string::size_type characterIndex = 0; characterIndex <
        r_std_str.length() ; ++ characterIndex)
      {
        put( (char_type) r_std_str.at(characterIndex) );
      }
      /**@see ostream.tcc */
      return *this;
    }
  };
}; //namespace css

#endif /* CSS_BASIC_STRINGSTREAM_HPP_ */
