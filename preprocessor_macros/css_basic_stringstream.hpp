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
namespace css
{
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

      //Return type for operator << for operands of single byte character type.
      //Must be a type of _this_ class, else following concatenations
      // via "<<" and single byte character are not possible when >>_CharT<<
      //is "wchar_t".
      typedef css::basic_stringstream<_CharT>    __ostream_type;
//      __ostream_type

      //Overwrite class std::basic_ostream's << operator because it returns a
      // std::basic_ostream object. but a css::basic_stringstream object is
      // needed.
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
      //Must return an object of _this_ type, else following concatenations
      // via "<<" and are not possible
      __ostream_type & operator<< (
          const char * p_ch)
      {
//        #error "css::basic_stringstream"
        #pragma message("css::basic_stringstream << const char * ")
//        return r_std_str;
        //return _M_insert<std::string>(r_std_str);
        //return

        for(short w = 0; p_ch[w] != '\0'; ++ w)
        {
          put( (char_type) p_ch[w] );
        }
        //see ostream.tcc
        return *this;
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
      __ostream_type & operator<< (
          const std::string & r_std_str)
      {
        #pragma message("css::basic_stringstream << const std::string & ")
//        return r_std_str;
        //return _M_insert<std::string>(r_std_str);
        //return
        for(short w = 0; w < r_std_str.length() ; ++ w)
        {
          put( (char_type) r_std_str.at(w) );
        }
        //see ostream.tcc
        return *this;
      }
  };
};

#endif /* CSS_BASIC_STRINGSTREAM_HPP_ */
