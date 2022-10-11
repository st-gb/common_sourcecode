///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Bln=BerLiN
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/Guard*/
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
  #if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
  ! defined TU_Bln361095cmnSrc_cxxopts_excTypes_hpp
  #define TU_Bln361095cmnSrc_cxxopts_excTypes_hpp

#ifndef _GLIBCXX_USE_C99_CTYPE_TR1///Avoid "already defined" compiler warning
/**For isblank(int) to be in namespace "std" in file <c++/cctype> (at least
 * in MinGW). This is needed for cxxopts.hpp */
  #define _GLIBCXX_USE_C99_CTYPE_TR1
#endif

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <preprocessor_macros/stringize.h>///stringize(...)

/**C++ needs to be >= 201103L for std::isblank in <c++/cctype> (for example 
 * MinGW32 9.2.0) */
#pragma message "__cplusplus:" stringize(__cplusplus)

///Needs header file from https://github.com/jarro2783/cxxopts
///For steps see https://github.com/jarro2783/cxxopts/blob/master/README.md
#include <cxxopts.hpp>///cxxopts::exceptions::exception from Jarryd Beck

namespace TU_Bln361095{namespace cxxopts{
/**Exception names changed from cxxopts::argument_incorrect_type at 12 Jul 2022
 * (see git history) Unfortunately the cxxopts version did not change at this
 * time.*/
#if CXXOPTS__VERSION_MAJOR > 2
  /**Must use sculp ("::") operator, else g++ (ver.7.5.0) compilation error(?)*/
  typedef ::cxxopts::exceptions::incorrect_argument_type incorrArgTypeExc;
  typedef ::cxxopts::exceptions::exception mostGenericExc;
#else
  /**Must use sculp ("::") operator, else g++ (ver.7.5.0) compilation error(?)*/
  typedef ::cxxopts::argument_incorrect_type incorrArgTypeExc;
  typedef ::cxxopts::OptionException mostGenericExc;
#endif
}}

#endif///#ifndef TU_Bln361095cmnSrc_cxxopts_excTypes_hpp
